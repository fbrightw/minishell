#include "../includes/minishell.h"

char	**alloc_mem_for_word(char **com, int k, char *fin_str)
{
	char	**new_com;
	int		i;

	i = 0;
	new_com = (char**)malloc(sizeof(char*) * (k + 1));
	while (com[i])
	{
		new_com[i] = com[i];
		i++;
	}
	new_com[i] = fin_str;
	new_com[i + 1] = 0;
	if (com)
		free(com);
	return (new_com);
}

void	word_with_spec_symbols(char **final_str, char **term_str, char *ch)
{
	char temp[2];

	temp[1] = '\0';
	temp[0] = **term_str;
	building_word(final_str, temp);
	(*term_str)++;
	while (**term_str && **term_str != ch[0])
	{
		temp[0] = **term_str;
		building_word(final_str, temp);
		(*term_str)++;
	}
	temp[0] = **term_str;
	building_word(final_str, temp);
	(*term_str)++;
}

void	add_word(t_var *var, char **term_str, char **final_str, int *k)
{
	char *type;

	if (*final_str)
	{
		if (check_if_pipe(*final_str))
			ft_split_pipes(var, *final_str, '|', k);
		else if (check_if_redir(var, *final_str, k))
			split_by_redirs(var, *final_str, k);
		else
			var->words = alloc_mem_for_word(var->words, *k, *final_str); // новая память ( старое кол-во слов + новое слово)
	}
	while (**term_str == ' ')
		(*term_str)++;
	*k += 1;
	*final_str = NULL;
}

void	delete_by_semicolon(char **term_str, t_var *var, int *k)
{
	char *final_str;

	final_str = NULL;
	while (**term_str && !ft_strchr(";", **term_str))
	{
		if (**term_str == ' ')
			add_word(var, term_str, &final_str, k);
		else if (ft_strchr("\'\"$?", **term_str))
			word_with_spec_symbols(&final_str, term_str, ft_strchr("\'\"$<>?", **term_str));
		else
		{
			var->temp[0] = **term_str;
			building_word(&final_str, var->temp);
			(*term_str)++;
		}
	}
	if (final_str)
	{
		k += 1;
		if (check_if_pipe(final_str))
			ft_split_pipes(var, final_str, '|', k);
		else if (check_if_redir(var, final_str, k))
			split_by_redirs(var, final_str, k);
		else
			var->words = alloc_mem_for_word(var->words, *k, final_str);
	}
}

void	find_cmds_args(t_list **com_in_str, char **term_str, t_all *main_struct, t_var *var)
{
	t_list	*inner_list;
	int k;
	int i;

	var->words = (char**)malloc(sizeof(char*));
	var->words[0] = NULL;
	var->temp[1] = '\0';
	k = 1;
	i = 0;

	delete_by_semicolon(term_str, var, &k);
	while (var->words[i])
	{
		if (symbols("\'\"\\$", var->words[i]))
			var->words[i] = deal_with_spec_smbls(*com_in_str, main_struct, var, var->words[i]);
		i++;
	}
	inner_list = NULL;
	divide_big_list(&inner_list, var, k);
	ft_lstadd_back(com_in_str, ft_lstnew(inner_list)); //течет
}

void	split_into_commands(char *term_str, t_all *main_struct, t_var *var)
{
	t_list *com_in_str;
	int i;

	i = 0;
	com_in_str = NULL;
	var->pipe_amount = 0;
	while (*term_str)
	{
		if (!ft_strchr(";", *term_str)) // not |;<>
		{
			while (*term_str == ' ')
				term_str++;
			find_cmds_args(&com_in_str, &term_str, main_struct, var);
		}
		else
			term_str++;
	}

	// printf("---------------WHAT WE HAVE IN ARRAY------------------\n");
	// while (com_in_str)
	// {
	// 	t_list *iner = (t_list*)(com_in_str->content);
	// 	while (iner)
	// 	{
	// 		int j = 0;
	// 		char **array = ((t_in_list*)(iner->content))->args;
	// 		while (array[j])
	// 		{
	// 			printf("%s\n", array[j]);
	// 			j++;
	// 		}
	// 		iner = iner->next;
	// 	}
	// 	com_in_str = com_in_str->next;
	// }
	// printf("------------------------------------------------------\n");

	while (com_in_str)
	{
		t_list *iner = (t_list*)(com_in_str->content);
		if (ft_lstsize(iner) == 1)
		{
			int j = 0;
			char **array = ((t_in_list*)(iner->content))->args;
			if (array[0])
				var->token = ft_strdup(array[0]);
			func(com_in_str, main_struct, var); // checking for built-in or other commands
		}
		// there are pipes
		// else
		// {

		// }
		com_in_str = com_in_str->next;
	}
}

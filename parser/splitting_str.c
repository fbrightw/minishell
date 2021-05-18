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

void	add_word(t_into_lists *vars, char **term_str, char **final_str, int *k)
{
	if (*final_str)
	{
		if (check_if_pipe(*final_str))
			ft_split_pipes(vars, *final_str, '|', k);
		else
			vars->args = alloc_mem_for_word(vars->args, *k, *final_str); // новая память ( старое кол-во слов + новое слово)
	}
	while (**term_str == ' ')
		(*term_str)++;
	*k += 1;
	*final_str = NULL;
}

void	find_cmds_args(t_list **com_in_str, char **term_str, t_all *main_struct, t_var *var)
{
	char temp[2];
	char *final_str = NULL;
	int k;
	int i;
	t_into_lists *vars = malloc(sizeof(t_into_lists));

	k = 1;
	i = 0;
	vars->args = (char**)malloc(sizeof(char*));
	vars->args[0] = NULL;
	vars->redirs = NULL;
	vars->pipes = NULL;
	temp[1] = '\0';

	while (**term_str && !ft_strchr(";", **term_str))
	{
		if (**term_str == ' ')
			add_word(vars, term_str, &final_str, &k);
		else if (ft_strchr("\'\"$<>?", **term_str))
			word_with_spec_symbols(&final_str, term_str, ft_strchr("\'\"$<>?", **term_str));
		else
		{
			temp[0] = **term_str;
			building_word(&final_str, temp);
			(*term_str)++;
		}
	}
	if (final_str)
	{
		k += 1;
		if (check_if_pipe(final_str))
			ft_split_pipes(vars, final_str, '|', &k);
		else
			vars->args = alloc_mem_for_word(vars->args, k, final_str);
	}
	while (vars->args[i])
	{
		if (symbols("\'\"\\$", vars->args[i]))
			vars->args[i] = deal_with_spec_smbls(*com_in_str, main_struct, var, vars->args[i]);
		i++;
	}

	// find indexes of redirections and pipes if they exist;
	indexes_of_pipe_red(vars);
	ft_lstadd_back(com_in_str, ft_lstnew(vars)); //течет
	if (!vars->pipes && !vars->redirs)
	{
		t_list *iter = *com_in_str;
		while (iter)
		{
			char *token = ((t_into_lists *)(iter->content))->args[0];
			func(iter, main_struct, var, token);
			iter = iter->next;
		}
	}
	else if (!vars->pipes)
		redirs(*com_in_str, vars, main_struct, var);
}

void	split_into_commands(char *term_str, t_all *main_struct, t_var *var)
{
	t_list *com_in_str;
	int pipe_amount;
	int i;

	i = 0;
	com_in_str = NULL;
	pipe_amount = 0;
	printf("str splitting = %s\n", term_str);
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
	// 	i = 0;
	// 	char **array =  ((t_into_lists *)(com_in_str->content))->args;
	// 	// printf("\n");
	// 	while (array[i])
	// 	{
	// 		printf("%s\n ", array[i]);
	// 		i++;
	// 	}
	// 	com_in_str = com_in_str->next;
	// }
	// printf("------------------------------------------------------\n");

	// count_pipes(com_in_str, &pipe_amount); //не учитывала что может быть |wc-c (слитно со сл командой)
	// // printf("pipe amount = %d\n", pipe_amount);
	// if (!pipe_amount)
	// 	func(com_in_str, main_struct, var); // checking for built-in or other commands
	// else
	// 	str_with_pipes(main_struct, com_in_str, pipe_amount);
}

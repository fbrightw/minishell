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

void	divide_by_semicolon(char **term_str, t_var *var, int *k)
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
		*k += 1;
		if (check_if_pipe(final_str))
			ft_split_pipes(var, final_str, '|', k);
		else if (check_if_redir(var, final_str, k))
			split_by_redirs(var, final_str, k);
		else
			var->words = alloc_mem_for_word(var->words, *k, final_str);
	}
}

void	find_cmds_args(t_list **com_in_str, char **term_str, t_var *var)
{
	t_list	*pipe_list;
	int k;
	int i;

	pipe_list = NULL;
	var->words = (char**)malloc(sizeof(char*));
	var->words[0] = NULL;
	var->temp[1] = '\0';
	k = 1;
	i = 0;

	divide_by_semicolon(term_str, var, &k);
	while (var->words[i])
	{
		if (symbols("\'\"\\$", var->words[i]))
			var->words[i] = deal_with_spec_smbls(*com_in_str, var, var->words[i]);
		i++;
	}
	divide_big_list(&pipe_list, var, k);
	ft_lstadd_back(com_in_str, ft_lstnew(pipe_list)); //течет
}

void	split_into_commands(char *term_str, t_var *var, struct termios term1)
{
	t_list *com_in_str;
	int i;

	i = 0;
	com_in_str = NULL;
	tcsetattr(0, TCSANOW, &term1);
	while (*term_str)
	{
		if (!ft_strchr(";", *term_str)) // not |;<>
		{
			while (*term_str == ' ')
				term_str++;
			find_cmds_args(&com_in_str, &term_str, var);
		}
		else
			term_str++;
	}
	execute_part(com_in_str, var);
}

#include "../includes/minishell.h"

void	add_word(t_var *var, char **term_str, char *final_str, int *k)
{
	if (final_str)
	{
		if (check_if_pipe(final_str))
		{
			ft_split_pipes(var, final_str, '|', k);
			free(final_str);
		}
		else if (check_if_redir(var, final_str, k))
		{
			split_by_redirs(var, final_str, k);
			free(final_str);
		}
		else
			var->words = alloc_mem_for_word(var->words, *k, final_str); //free(final_str)
	}
	while (**term_str == ' ')
		(*term_str)++;
	*k += 1;
}

void	divide_by_semicolon(char **term_str, t_var *var, int *k)
{
	char *final_str;

	final_str = NULL;
	while (**term_str && !ft_strchr(";", **term_str))
	{
		if (**term_str == ' ')
		{
			add_word(var, term_str, final_str, k);
			final_str = NULL;
		}
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
		add_word(var, term_str, final_str, k);
		final_str = NULL;
	}
}

void	find_cmds_args(t_list **com_in_str, char **term_str, t_var *var)
{
	char *temp;
	t_list	*pipe_list;
	int k;
	int i;

	k = 1;
	i = 0;
	pipe_list = NULL;
	var->words = (char**)malloc(sizeof(char*));
	var->words[0] = NULL;
	var->temp[1] = '\0';
	divide_by_semicolon(term_str, var, &k);
	while (var->words[i])
	{
		if (symbols("\'\"\\$", var->words[i]))
		{
			temp = var->words[i];
			var->words[i] = deal_with_spec_smbls(*com_in_str, var, var->words[i]);
			free(temp);
		}
		i++;
	}
	divide_big_list(&pipe_list, var, k);
	ft_lstadd_back(com_in_str, ft_lstnew(pipe_list)); //течет
	free(var->words);
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
		if (!ft_strchr(";", *term_str))
		{
			while (*term_str == ' ')
				term_str++;
			find_cmds_args(&com_in_str, &term_str, var);
		}
		else
			term_str++;
	}
	execute_part(com_in_str, var);
	cleaning(com_in_str);
}

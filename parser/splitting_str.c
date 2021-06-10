#include "../includes/minishell.h"

void	add_word(t_var *var, char **term_str, char **final_str, int *k)
{
	if (*final_str)
	{
		if (check_if_pipe(*final_str))
		{
			ft_split_pipes(var, *final_str, '|', k);
			free(*final_str);
		}
		else if (check_if_redir(var, *final_str, k))
		{
			split_by_redirs(var, *final_str, k);
			free(*final_str);
		}
		else
		{
			*k += 1;
			var->words = alloc_mem_for_word(var->words, *k, *final_str);
		}
	}
	while (**term_str == ' ')
		(*term_str)++;
	*final_str = NULL;
}

void	remain(t_var *var, char **term_str, char **final_str, int *k)
{
	if (var->syntax_fl)
		return ;
	if (*final_str)
	{
		add_word(var, term_str, final_str, k);
		*final_str = NULL;
	}
}

void	divide_by_semicolon(char **term_str, t_var *var, int *k)
{
	char	*final_str;
	int		fl;

	final_str = NULL;
	fl = 0;
	while (**term_str && !ft_strchr(";", **term_str))
	{
		fl = 1;
		if (**term_str == ' ')
			add_word(var, term_str, &final_str, k);
		else if (ft_strchr("\'\"", **term_str))
			word_with_spec_symbols(&final_str, term_str, \
			ft_strchr("\'\"", **term_str));
		else
		{
			var->temp[0] = **term_str;
			building_word(&final_str, var->temp);
			(*term_str)++;
		}
	}
	if (!fl)
		var->syntax_fl = 1;
	remain(var, term_str, &final_str, k);
}

void	define_variables(t_var *var, int *k)
{
	*k = 0;
	var->words = (char **)malloc(sizeof(char *));
	var->words[0] = NULL;
	var->temp[1] = '\0';
	var->fl = 1;
}

int	work_with_spec_smbls(t_var *var, t_list **com_in_str)
{
	char	*temp;
	int		i;

	temp = NULL;
	i = 0;
	while (var->words[i])
	{
		if (symbols("\'\"\\$", var->words[i]))
		{
			temp = var->words[i];
			var->words[i] = deal_spec_smbls(*com_in_str, var, var->words[i]);
			free(temp);
			if (var->syntax_fl)
			{
				free_var(var);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	find_cmds_args(t_list **com_in_str, char **term_str, t_var *var)
{
	t_list	*pipe_list;
	int		k;

	define_variables(var, &k);
	pipe_list = NULL;
	divide_by_semicolon(term_str, var, &k);
	check_for_syntax(var);
	if (var->syntax_fl)
		return (0);
	if (work_with_spec_smbls(var, com_in_str))
	{
		divide_big_list(&pipe_list, var, k);
		ft_lstadd_back(com_in_str, ft_lstnew(pipe_list));
		free(var->words);
		return (1);
	}
	return (0);
}

void	split_into_commands(char *term_str, t_var *var)
{
	t_list	*com_in_str;

	com_in_str = NULL;
	while (*term_str)
	{
		if (!ft_strchr(";", *term_str))
		{
			while (*term_str == ' ')
				term_str++;
			if (!find_cmds_args(&com_in_str, &term_str, var))
				break ;
		}
		else
		{
			term_str++;
			if (!var->fl || *term_str == ';')
			{
				printf("syntax error near unexpected token ;\n");
				var->syntax_fl = 1;
				handle_syntax(com_in_str, var);
				return ;
			}
		}
	}
	handle_syntax(com_in_str, var);
}

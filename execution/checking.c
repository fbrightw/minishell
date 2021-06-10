#include "../includes/minishell.h"

char	*check_syntaxs_fl(t_var *var, char *command)
{
	if (var->syntax_fl)
	{
		if (command)
			free(command);
		command = NULL;
		return (NULL);
	}
	return (command);
}

void	backslash_in_dquotes(char **word, char **command, t_var *var)
{
	(*word)++;
	if (**word && **word != '\"')
	{
		if (!find_exact_symb("$\\", **word))
			building_word(command, "\\");
		var->temp[0] = **word;
		building_word(command, var->temp);
		(*word)++;
	}
	else
	{
		(*word)++;
		if (!**word)
		{
			printf("syntax error near unexpected token\n");
			var->syntax_fl = 1;
			return ;
		}
		else
		{
			var->temp[0] = '\"';
			var->temp[1] = 0;
			building_word(command, var->temp);
		}
	}
}

void	result_d_quotes(t_var *var, char **word)
{
	if (!**word)
	{
		var->syntax_fl = 1;
		printf("syntax error near unexpected token 1\n");
		return ;
	}
	else
		(*word)++;
}

void	input_error(t_reds *redirs, t_var *var, int *index)
{
	write(1, var->words[*index + 1], ft_strlen(var->words[*index + 1]));
	write(1, " : ", 3);
	printf("%s\n", strerror(errno));
	var->status = 1;
	var->fl_error = 1;
	redirs->type = -1;
}

void	check_for_syntax(t_var *var)
{
	int	i;

	i = 0;
	if (!ft_strcmp(var->words[i], "|"))
	{
		printf("syntax error near unexpected token | \n");
		var->syntax_fl = 1;
		free_var(var);
		return ;
	}
	while (var->words[i])
	{
		if (!ft_strcmp(var->words[i], "|"))
		{
			if (!var->words[i + 1] || !ft_strcmp(var->words[i + 1], "|"))
			{
				printf("syntax error near unexpected token | \n");
				var->syntax_fl = 1;
				free_var(var);
				return ;
			}
		}
		else if (!var->words[i + 1] && !ft_strcmp(var->words[i], "\\"))
		{
			printf("syntax error near unexpected token \\ \n");
			var->syntax_fl = 1;
			free_var(var);
			return ;
		}
		i++;
	}
	if (var->fl == 2)
		printf("syntax error near unexpected token ;\n");
}

void	handle_syntax(t_list *com_in_str, t_var *var)
{
	int	i;

	i = 0;
	if (!var->syntax_fl)
	{
		execute_part(com_in_str, var);
		cleaning(com_in_str);
		return ;
	}
	else
	{
		if (com_in_str && ft_lstsize(com_in_str) > 0)
			cleaning(com_in_str);
		return ;
	}
}

void	free_var(t_var *var)
{
	int	i;

	i = 0;
	while (var->words[i])
	{
		free(var->words[i]);
		i++;
	}
	free(var->words);
}

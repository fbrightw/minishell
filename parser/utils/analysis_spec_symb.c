#include "../../includes/minishell.h"

void	quot_in_dquots(t_var *var, char **command, char **word)
{
	char	*str;

	str = NULL;
	building_word(command, "\'");
	(*word)++;
	while (**word == '$')
	{
		dollar(word, var, command);
		while (**word == '\'')
		{
			building_word(command, "'");
			(*word)++;
		}
	}
	if (**word != '\'' && **word != '\"')
	{
		var->temp[0] = **word;
		building_word(command, var->temp);
		(*word)++;
	}
	else if (**word == '\'')
	{
		building_word(command, "\'");
		(*word)++;
	}
}

int	after_while(char **word, char **var_in_env, t_var *var, char **command)
{
	if (**word == '\"')
	{
		*var_in_env = find_variable_in_env(var->general, *var_in_env, 0);
		if (*var_in_env[0] != '\0')
		{
			building_word(command, *var_in_env);
			return (1);
		}
		return (1);
	}
	else
	{
		var->syntax_fl = 1;
		printf("syntax error near unexpected token\n");
		return (0);
	}
}

int	dquots_while(t_var *var, char **word, char **cmd, char **var_in_env)
{
	while (**word && **word != '\"')
	{
		if (**word != '\'')
		{
			if (**word == '\\')
			{
				backslash(word, cmd, var);
				return (0);
			}
			var->temp[0] = **word;
			building_word(var_in_env, var->temp);
			(*word)++;
		}
		else
			quot_in_dquots(var, cmd, word);
	}
	return (after_while(word, var_in_env, var, cmd));
}

int	no_backslash(t_var *var, char **word, char **command)
{
	char	*var_in_env;

	var_in_env = NULL;
	(*word)++;
	while (**word && **word == '$')
	{
		building_word(&var_in_env, "$");
		(*word)++;
	}
	return (dquots_while(var, word, command, &var_in_env));
}

int	dollar_in_quot(t_var *var, char **word, char **command)
{
	char	*var_in_env;
	char	temp[2];

	var_in_env = NULL;
	temp[1] = '\0';
	while (**word)
	{
		if ((*word)[1] != '\\')
			return (no_backslash(var, word, command));
		else
		{
			temp[0] = **word;
			building_word(command, temp);
			(*word)++;
			return (1);
		}
	}
	return (1);
}

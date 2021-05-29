#include "../../includes/minishell.h"

int		find_exact_symb(char *symbols, char c)
{
	while (*symbols)
	{
		if (*symbols == c)
			return (1);
		symbols++;
	}
	return (0);
}

int	symbols(char *sym, char *word)
{
	while (*sym)
	{
		if (!ft_strchr(word, *sym))
			sym++;
		else
			return (1);
	}
	return (0);
}

void	backslash(char **word, char **command, t_var *var)
{
	(*word)++;
	if (!**word)
	{
		write(1, "Error: multiline commands\n", 27);
		exit(0);
	}
	var->temp[1] = '\0';
	var->temp[0] = **word;
	building_word(command, var->temp);
	(*word)++;
}

int	no_backslash(t_var *var, char **word, char **command)
{
	char *var_in_env = NULL;
	(*word)++;
	// if ($)
	while (**word && **word != '\"')
	{
		var->temp[0] = **word;
		building_word(&var_in_env, var->temp);
		(*word)++;
	}
	if (**word == '\"')
	{
		if ((var_in_env = find_variable_in_env(var->general, var_in_env, 0))[0] != '\0')
		{
			building_word(command, var_in_env);
			return (1);
		}
		else
			return (1);
	}
	else
	{
		write(1, "Error: multiline commands\n", 27);
		exit(0);
	}
}

int	dollar_in_quot(t_var *var, char **word, char **command)
{
	char *var_in_env = NULL;
	char temp[2];

	temp[1] = '\0';
	while (**word)
	{
		if ((*word)[1] != '\\')
			return(no_backslash(var, word, command));
		else
		{
			temp[0] = **word;
			building_word(command, var_in_env);
			building_word(command, temp);
			(*word)++;
			return(1);
		}
	}
	return (1);
}

void	dollar(char **word, t_var *var, char **command)
{
	char *temp = NULL;
	char *str = NULL;

	var->temp[1] = '\0';
	(*word)++;
	while (**word && !find_exact_symb("\'\"$\\", **word))
	{
		var->temp[0] = **word;
		if (!temp)
			temp = ft_strdup(var->temp);
		else
			temp = ft_strjoin(temp, var->temp);
		(*word)++;
	}
	str = find_variable_in_env(var->general, temp, 0);
	if (!str)
	{
		if (!*command)
			*command = ft_strdup("$");
		else
			*command = ft_strjoin(*command, "$");
	}
	else if (str[0] == '\0')
		(*word)++;
	else
	{
		if (!*command)
			*command = ft_strdup(str);
		else
			*command = ft_strjoin(*command, str);
	}
}

void	single_quotes(char **word, t_var *var, char **command)
{
	(*word)++;
	while (**word && **word != '\'')
	{
		var->temp[0] = **word;
		building_word(command, var->temp);
		(*word)++;
	}
	if (!(**word))
	{
		write(1, "Error: multiline commands\n", 27);
		exit(0);
	}
	else
		(*word)++;
}

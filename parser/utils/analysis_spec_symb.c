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
	// printf("%s\n", *command);
	(*word)++;
	var->temp[1] = '\0';
	var->temp[0] = **word;
	building_word(command, var->temp);
	(*word)++;
}

void	dollar_in_quot(char **word, t_all *main_struct, char **command)
{
	char *var_in_env = NULL;
	char temp[2];

	temp[1] = '\0';
	while (**word)
	{
		if ((*word)[1] != '\\')
		{
			(*word)++;
			// if (**word == '$')
				// error
			while (**word && **word != '\"')
			{
				temp[0] = **word;
				building_word(&var_in_env, temp);
				(*word)++;
			}
			if (**word == '\"')
			{
				if ((var_in_env = find_variable_in_env(main_struct, var_in_env, 0))[0] != '\0')
				{
					// printf("var %s\n", var_in_env);
					if (!*command)
						*command = ft_strdup(var_in_env);
					else
						*command = ft_strjoin(*command, var_in_env);
					printf("ERROR %s\n", *command);
					break;
				}
				else
					break;
			}
			else
			{
				printf("ERROR %s\n", *command);
				break;
				exit(0);
			}
		}
		else
		{
			temp[0] = **word;
			building_word(command, var_in_env);
			building_word(command, temp);
			(*word)++;
			break;
		}
	}
}

void	dollar(char **word, t_all *main_struct, t_var *var, char **command)
{
	char *temp = NULL;
	char *str = NULL;

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
	str = find_variable_in_env(main_struct, temp, 0);
	if (str[0] == '\0')
		(*word)++;
	else
	{
		if (!*command)
			*command = ft_strdup(str);
		else
			*command = ft_strjoin(*command, str);
	}
}

void	single_quotes(char **word, t_all *main_struct, t_var *var, char **command)
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
		printf("%s\n", *command);
		write(1, "ERROR QUOT\n", 12);
		exit(0);
	}
	else
		(*word)++;
}

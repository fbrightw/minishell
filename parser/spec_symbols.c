#include "../includes/minishell.h"

void	building_word(char **str1, char *str2)
{
	if (!*str1)
		*str1 = ft_strdup(str2);
	else
		*str1 = ft_strjoin(*str1, str2);
}


void	backslash_in_double(char **word, char **command, t_var *var)
{
	(*word)++;
	var->temp[1] = '\0';
	var->temp[0] = **word;
	building_word(command, var->temp);
	(*word)++;
}

void	double_quotes(char **word, t_var *var, t_all *main_struct, char **command)
{
	// var->quot++;
	while (**word && **word != '\"')
	{
		if (**word == '$')
			dollar_in_quot(word, main_struct, command);
		else if (**word == '\\')
		{
			if (find_exact_symb("\\\"$", (*word)[1]))
				backslash(word, command, var);
			else
			{
				building_word(command, "\\");
				(*word)++;
			}
		}
		else
		{
			var->temp[0] = **word;
			building_word(command, var->temp);
			(*word)++;
		}
	}
	if (!**word)
	{
		printf("%s\n", *command);
		write(1, "ERROR double Quot\n", 19);
		exit(0);
	}
	else
		(*word)++;
}

char	*deal_with_spec_smbls(t_list *com_in_str, t_all *main_struct, t_var *var, char *word)
{
	int i;
	char *command = NULL;

	i = 0;
	var->temp[1] = '\0';

	while (*word)
	{
		if (*word == '\'')  // если увидели кавычки, то приписываем то что внутри
			single_quotes(&word, main_struct, var, &command);
		else if (*word == '\"')
		{
			word++;
			double_quotes(&word, var, main_struct, &command);
		}
		else if (*word == '$')
			dollar(&word, main_struct, var, &command);
		else if (*word == '\\')
			backslash(&word, &command, var);
		else
		{
			var->temp[0] = *word;
			building_word(&command, var->temp);
			word++;
		}
	}
	// printf("command %s\n", command);
	return (command);
}

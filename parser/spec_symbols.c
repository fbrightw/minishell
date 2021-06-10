#include "../includes/minishell.h"

void	dollar(char **word, t_var *var, char **command)
{
	char	*var_in_env;

	var_in_env = NULL;
	(*word)++;
	while (**word && !find_exact_symb("\'\"\\$?/", **word))
	{
		var->temp[0] = **word;
		building_word(&var_in_env, var->temp);
		(*word)++;
	}
	join_st_or_envs_var(var, var_in_env, word, command);
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
		printf("syntax error near unexpected token\n");
		var->syntax_fl = 1;
		return ;
	}
	else
		(*word)++;
}

void	double_quotes(char **word, t_var *var, char **command)
{
	(*word)++;
	while (**word && **word != '\"')
	{
		if (var->syntax_fl)
			return ;
		if (**word == '$')
			dollar_in_quot(var, word, command);
		else if (**word == '\\')
			backslash_in_dquotes(word, command, var);
		else if (**word == '\'')
			quot_in_dquots(var, command, word);
		else
		{
			var->temp[0] = **word;
			building_word(command, var->temp);
			(*word)++;
		}
	}
	if (!var->syntax_fl)
		result_d_quotes(var, word);
}

void	backslash(char **word, char **command, t_var *var)
{
	(*word)++;
	if (**word)
	{
		var->temp[0] = **word;
		building_word(command, var->temp);
		(*word)++;
	}
	else
	{
		printf("syntax error near unexpected token \n");
		var->syntax_fl = 1;
	}
}

char	*deal_spec_smbls(t_list *com_in_str, t_var *var, char *word)
{
	char	*command;

	command = NULL;
	var->temp[1] = '\0';
	while (*word)
	{
		if (var->syntax_fl)
			break ;
		if (*word == '\'')
			single_quotes(&word, var, &command);
		else if (*word == '\"')
			double_quotes(&word, var, &command);
		else if (*word == '$')
			dollar(&word, var, &command);
		else if (*word == '\\')
			backslash(&word, &command, var);
		else
		{
			var->temp[0] = *word;
			building_word(&command, var->temp);
			word++;
		}
	}
	return (check_syntaxs_fl(var, command));
}

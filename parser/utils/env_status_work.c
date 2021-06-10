#include "../../includes/minishell.h"

char	*return_from_env(char *variable, char *final_str, int fl_to_free)
{
	if (!variable)
		return (NULL);
	if (!final_str)
	{
		final_str = malloc(sizeof(char));
		final_str[0] = '\0';
	}
	if (fl_to_free)
		free(variable);
	return (final_str);
}

char	*find_variable_in_env(t_all *main_struct, char *varible, int fl_to_free)
{
	char	*final_str;
	int		i;

	i = 0;
	final_str = NULL;
	while (main_struct->envs->env_arr[i] && varible)
	{
		if (!ft_strncmp(varible, \
		main_struct->envs->env_arr[i], ft_strlen(varible))
			&& main_struct->envs->env_arr[i][ft_strlen(varible)] == '=')
		{
			final_str = main_struct->envs->env_arr[i] + ft_strlen(varible) + 1;
			break ;
		}
		else
			i++;
	}
	return (return_from_env(varible, final_str, fl_to_free));
}

void	get_status(t_var *var, char **word, char **command)
{
	char	*str1;

	var->general->state = var->status;
	str1 = ft_itoa(var->status);
	(*word)++;
	building_word(command, str1);
	if (str1)
		free(str1);
}

void	join_st_or_envs_var(t_var *var, char *in_env, char **word, char **com)
{
	char	*str;

	if (in_env)
	{
		str = find_variable_in_env(var->general, in_env, 1);
		if (!str)
			building_word(com, "$");
		else if (str[0] == '\0')
			(*word)++;
		else
			building_word(com, str);
	}
	else
	{
		if (**word == '?')
			get_status(var, word, com);
		else if (**word == '/')
		{
			building_word(com, "$/");
			(*word)++;
		}
		else if (!**word)
			building_word(com, "$");
	}
}

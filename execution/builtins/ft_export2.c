/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvinnie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 17:35:35 by rvinnie           #+#    #+#             */
/*   Updated: 2021/06/08 17:35:36 by rvinnie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_argument(char *to_export, char *arg, char **vars)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i++] == '=')
		{
			to_export = ft_strdup(arg);
			return (to_export);
		}
	}
	i = 0;
	while (vars[i])
	{
		if (ft_strncmp(vars[i], arg, ft_strlen(arg)) == 0
			&& vars[i][ft_strlen(arg)] == '=')
		{
			to_export = ft_strdup(vars[i]);
			return (to_export);
		}
		i++;
	}
	to_export = ft_strdup(arg);
	return (to_export);
}

int	is_in_arr(char **env, char *to_export)
{
	int		len;
	int		i;

	len = 0;
	while (to_export[len] != '=' && to_export[len] != '\0')
		len++;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], to_export, len) == 0)
		{
			if (env[i][len] == '=' || env[i][len] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}

char	**add_el(t_all *main_struct, char **env, char *to_export, int len)
{
	int		i;
	char	**new_arr;

	i = 0;
	new_arr = malloc((len + 2) * sizeof(char *));
	if (!new_arr)
	{
		error_msg("failed to allocate memory", 0, main_struct, 1);
		free_arr(env);
		exit(1); // replace with your function
	}
	i = 0;
	while (env[i])
	{
		new_arr[i] = env[i];
		i++;
	}
	free(env);
	new_arr[i++] = to_export;
	new_arr[i] = NULL;
	return (new_arr);
}

char	**rebuild_env(t_all *main_struct, char **env, char *to_export, int len)
{
	int		place;
	int		is_full;
	int		i;

	place = is_in_arr(env, to_export);
	is_full = 0;
	i = 0;
	while (to_export[i])
	{
		if (to_export[i++] == '=')
			is_full = 1;
	}
	if (is_full == 0 && place > -1)
		return (env);
	if (place == -1)
		env = add_el(main_struct, env, to_export, len);
	else
	{
		free(env[place]);
		env[place] = to_export;
	}
	return (env);
}

char	**add_vars(t_all *main_struct, char **env, char *arg, char **vars)
{
	char	**new_arr;
	int		len;
	char	*to_export;

	len = get_arr_len(env);
	to_export = check_argument(to_export, arg, vars);
	if (!to_export)
	{
		error_msg("failed to allocate memory", 0, main_struct, 1);
		exit(1); // replace with your function
	}
	env = rebuild_env(main_struct, env, to_export, len);
	return (env);
}

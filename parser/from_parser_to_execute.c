#include "../includes/minishell.h"
int	is_it_b(char *token, t_var *var)
{
	int i;
	int j;
	int k;

	i = -1;
	j = 0;
	while (var->builtins[j])
	{
		k = 0;
		i = 0;
		while (token[i] && (token[i] == ft_toupper((var->builtins[j])[k]) || token[i] == ((var->builtins[j])[k])))
		{
			i++;
			k++;
		}
		if (!(token[i]) && !(var->builtins[j][k]))
		{
			free(var->token);
			var->token = ft_strdup(var->builtins[j]);
			return (1);
		}
		j++;
	}
	return (0);
}

void	func(t_list *pipe_list, t_var *var)
{
	char **args = ((t_in_list*)(pipe_list->content))->args;
	if (var->token)
	{
		if (is_it_b(var->token, var))
		{
			if (!strcmp(var->token, "echo"))
				ft_echo(var->general, args);
			else if (!strcmp(var->token, "cd"))
				ft_cd(var->general, args);
			else if (!strcmp(var->token, "pwd"))
				ft_pwd(var->general, args);
			else if (!strcmp(var->token, "export"))
				ft_export(var->general, args);
			else if (!strcmp(var->token, "unset"))
				ft_unset(var->general, args);
			else if (!strcmp(var->token, "exit"))
				ft_exit(var->general, args);
			else if (!strcmp(var->token, "env"))
				ft_env(var->general, args);
		}
		else
			other_command(var, pipe_list, var->token);
	}
}

void	execute_part(t_list *com_in_str, t_var *var)
{
	t_list *pipe_list;

	while (com_in_str)
	{
		pipe_list = (t_list*)(com_in_str->content);
		if (ft_lstsize(pipe_list) == 1)
		{
			int j = 0;
			char **array = ((t_in_list*)(pipe_list->content))->args;
			if (array[0])
				var->token = ft_strdup(array[0]);
			func(pipe_list, var);
		}
		else
			handle_pipes(&pipe_list, var);
		com_in_str = com_in_str->next;
	}
}

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
	int i;
	char *final_str;

	i = 0;
	final_str = NULL;
	while (main_struct->envs->env_arr[i] && varible)
	{
		if (!ft_strncmp(varible, main_struct->envs->env_arr[i], ft_strlen(varible))
			&& main_struct->envs->env_arr[i][ft_strlen(varible)] == '=')
		{
			final_str = ft_substr(main_struct->envs->env_arr[i], ft_strlen(varible)+ 1,
				ft_strlen(main_struct->envs->env_arr[i]) - ft_strlen(varible) - 1);
			break;
		}
		else
			i++;
	}
	return(return_from_env(varible, final_str, fl_to_free));
}

int	check_work_redirs(t_list *pipe_list)
{
	t_list *reds_struct =  ((t_in_list*)(pipe_list->content))->reds_struct;
	while (pipe_list)
	{
		while (reds_struct)
		{
			t_reds *reds = (t_reds*)(reds_struct->content);
			int type = reds->type;
			if (type == 0)
				redir_input(reds);
			else if (type == 1)
				redir_outputs(reds, "OUTPUT");
			else if (type == 2)
				redir_outputs(reds, "APP_OUTPUT");
			else if (type == -1)
				write(1, "ERROR\n", 3);
			reds_struct = reds_struct->next;
		}
		pipe_list = pipe_list->next;
	}
	return (1);
}

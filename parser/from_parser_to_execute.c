#include "../includes/minishell.h"

void	execute_part(t_list *com_in_str, t_var *var)
{
	t_list *pipe_list;

	while (com_in_str)
	{
		pipe_list = (t_list*)(com_in_str->content);
		if (ft_lstsize(pipe_list) == 1) // нет пайпа
		{
			int j = 0;
			char **array = ((t_in_list*)(pipe_list->content))->args;
			if (array[0])
				var->token = ft_strdup(array[0]);
			func(pipe_list, var); // checking for built-in or other commands
		}
		else
			handle_pipes(&pipe_list, var);
		com_in_str = com_in_str->next;
	}
}

char	*find_variable_in_env(t_all *main_struct, char *varible, int fl_to_free)
{
	int i;
	char *final_str;

	i = 0;
	final_str = NULL;
	while (main_struct->env[i] && varible)
	{
		if (!ft_strncmp(varible, main_struct->env[i], ft_strlen(varible)) && main_struct->env[i][ft_strlen(varible)] == '=')
		{
			final_str = ft_substr(main_struct->env[i], ft_strlen(varible)+ 1, ft_strlen(main_struct->env[i]) - ft_strlen(varible) - 1);
			break;
		}
		else
			i++;
	}
	if (!varible)
		return (NULL);
	if (!final_str)
	{
		final_str = malloc(sizeof(char));
		final_str[0] = '\0';
	}
	if (fl_to_free)
		free(varible);
	return (final_str);
}

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

int	check_work_redirs(t_list *pipe_list)
{
	t_list *reds_struct =  ((t_in_list*)(pipe_list->content))->reds_struct;
	while (pipe_list)
	{
		while (reds_struct)
		{
			// write(1, "YA\n", 3);
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

void	func(t_list *pipe_list, t_var	*var)
{
	if (var->token)
	{
		if (is_it_b(var->token, var))

			// printf("\nYES, built in\n");
			// other_command(var, pipe_list, var->token);
			printf("%s\n", var->token);
		else
			other_command(var, pipe_list, var->token);
	}
}

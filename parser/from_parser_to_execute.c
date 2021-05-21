#include "../includes/minishell.h"

char	*find_variable_in_env(t_all *main_struct, char *varible, int fl_to_free)
{
	int i;
	char *final_str;

	i = 0;
	final_str = NULL;
	while (main_struct->env[i])
	{
		if (!ft_strncmp(varible, main_struct->env[i], ft_strlen(varible)) && main_struct->env[i][ft_strlen(varible)] == '=')
		{
			final_str = ft_substr(main_struct->env[i], ft_strlen(varible)+ 1, ft_strlen(main_struct->env[i]) - ft_strlen(varible) - 1);
			break;
		}
		else
			i++;
	}
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
			return (1);
		j++;
	}
	return (0);
}

int	check_work_redirs(t_list *inner, t_all *main_struct)
{
	t_list *in_inner =  ((t_in_list*)(inner->content))->redirs;

	while (inner)
	{
		// if (input || output || app_out)
		// {
		// 	if (!strcmp(input, "absent") ||
		// 	!strcmp(output, "absent") ||
		// 	!strcmp(app_out, "absent"))
		// 		write(1, "ERROR\n", 6);
		// }
		// else
		{
			while (in_inner)
			{
				t_reds *reds = (t_reds*)(in_inner->content);
				char *redir = reds->redir;
				int type = reds->type;
				if (type == 0)
					redir_input(main_struct, redir);
				else if (type == 1)
					redir_outputs(main_struct, redir, "OUTPUT");
				else if (type == 2)
					redir_outputs(main_struct, redir, "APP_OUTPUT");
				else if (type == -1)
					write(1, "ERROR\n", 3);
				in_inner = in_inner->next;
			}
		}
		inner = inner->next;
	}
	return (1);
}

void	func(t_list *com_in_str, t_all *main_struct, t_var	*var)
{
	// printf("token %s\n", var->token);
	if (var->token)
	{
		if (is_it_b(var->token, var))
			printf("\nYES, built in\n");
		else
		{
			t_list *inner = (t_list*)(com_in_str->content);
			char **args = ((t_in_list*)(inner->content))->args;
			other_command(main_struct, inner, args, var->token);
		}
	}
}

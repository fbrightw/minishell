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

void	func(t_list *com_in_str, t_all *main_struct, t_var	*var, char *token)
{
	if (token)
	{
		if (is_it_b(token, var))
			printf("\nYES, built in\n");
		else
		{
			char **args = ((t_into_lists*)(com_in_str->content))->args;
			other_command(args, token, main_struct);
			// printf("NO, just something else\n");
		}
	}
}

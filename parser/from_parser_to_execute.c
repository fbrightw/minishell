#include "../includes/minishell.h"

int	is_it_b(char *token, t_var *var)
{
	char *builtins[7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int i;
	int j;
	int k;

	i = -1;
	j = 0;
	while (builtins[j])
	{
		k = 0;
		i = 0;
		while (token[i] && (token[i] == ft_toupper((builtins[j])[k]) || token[i] == ((builtins[j])[k])))
		{
			i++;
			k++;
		}
		if (!(token[i]) && !(builtins[j][k]))
		{
			free(var->token);
			var->token = ft_strdup(builtins[j]);
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
	t_reds *redirs;
	char **array;

	var->stdin = dup(STDIN_FILENO); //remember stds
	var->stdout = dup(STDOUT_FILENO);
	while (com_in_str)
	{
		pipe_list = (t_list*)(com_in_str->content);
		if (ft_lstsize(pipe_list) == 1)
		{
			array = ((t_in_list*)(pipe_list->content))->args;
			if (array[0])
				var->token = array[0];
			if (check_work_redirs(pipe_list, var))
				func(pipe_list, var);
			dup2(var->stdin, 0);
			dup2(var->stdout, 1);
		}
		else
			handle_pipes(pipe_list, var);
		com_in_str = com_in_str->next;
	}
}

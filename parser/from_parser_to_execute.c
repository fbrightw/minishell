#include "../includes/minishell.h"

void	path_exist(t_list *pipe_list, t_var *var, char **args)
{
	if (!ft_strcmp(var->token, "echo"))
	{
		ft_echo(var->general, args);
		var->status = var->general->state;
	}
	else if (!ft_strcmp(var->token, "cd"))
	{
		ft_cd(var->general, args);
		var->status = var->general->state;
	}
	else if (!ft_strcmp(var->token, "pwd"))
		ft_pwd(var->general, args);
	else if (!ft_strcmp(var->token, "export"))
		ft_export(var->general, args);
	else if (!ft_strcmp(var->token, "unset"))
		ft_unset(var->general, args);
	else if (!ft_strcmp(var->token, "exit"))
		ft_exit(var->general, args);
	else if (!ft_strcmp(var->token, "env"))
		ft_env(var->general, args);
	else
		other_command(var, pipe_list, var->token);
}

void	change_state(t_var *var)
{
	if (WIFEXITED(var->status))
		var->status = WEXITSTATUS(var->status);
	else if (WIFSIGNALED(var->status))
		var->status = WTERMSIG(var->status) + 128;
	else if (WIFSTOPPED(var->status))
		var->status = 128 + WSTOPSIG(var->status);
}

void	func(t_list *pipe_list, t_var *var)
{
	char	**args;
	pid_t	pid;
	int		result;

	args = ((t_in_list *)(pipe_list->content))->args;
	if (var->token)
	{
		result = check_if_bin_file(var, var->token);
		if (result == 1)
		{
			pid = fork();
			if (pid == 0)
				exec_bin_file(var, var->token, args);
			waitpid(pid, &(var->status), 0);
			change_state(var);
			return ;
		}
		else if (result == 0)
			not_bin_file(pipe_list, var, args);
		else
			return ;
	}
}

void	without_pipes(t_var *var, char **array, t_list *pipe_list)
{
	array = ((t_in_list *)(pipe_list->content))->args;
	if (array[0])
		var->token = array[0];
	if (check_work_redirs(pipe_list, var))
		func(pipe_list, var);
	dup2(var->stdin, 0);
	dup2(var->stdout, 1);
}

void	execute_part(t_list *com_in_str, t_var *var)
{
	t_list	*pipe_list;
	t_reds	*redirs;
	char	**array;

	var->stdin = dup(STDIN_FILENO);
	var->stdout = dup(STDOUT_FILENO);
	while (com_in_str)
	{
		pipe_list = (t_list *)(com_in_str->content);
		if (ft_lstsize(pipe_list) == 1)
			without_pipes(var, array, pipe_list);
		else
		{
			var->procces_quant = ft_lstsize(pipe_list);
			handle_pipes(pipe_list, var);
		}
		com_in_str = com_in_str->next;
	}
}

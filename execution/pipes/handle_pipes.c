#include "../../includes/minishell.h"

void	handle_pipes(char **array, int pipe_amount)
{
	int i;
	int tmp_fdin;
	int tmp_fdout;
	int pipes[pipe_amount][2]; // create fd's, fd_out[0] - read, fd_in[1] - write;

	i = 0;
	tmp_fdin = dup(0);
	tmp_fdout = dup(1);

	int fd_in = dup(tmp_fdin);
	while (i < pipe_amount)
	{
		pipe(pipes[i]);
		i++;
	}
}

void	str_with_pipes(t_list *com_in_str, int pipe_amount)
{
	int i;
	int quant_simple_cmds;
	char **array;

	quant_simple_cmds = 0;
	while (com_in_str)
	{
		i = 0;
		array =  ((t_into_lists *)(com_in_str->content))->args;
		while (array[i])
		{
			if (*array[i] == '|')
				quant_simple_cmds++;
			i++;
		}
		handle_pipes(array, quant_simple_cmds);
		com_in_str = com_in_str->next;
	}
}

#include "../../includes/minishell.h"

// void	handle_pipes(t_all *main_struct, char **array, int pipe_amount)
// {

// }


// void	handle_pipes(t_all *main_struct, char **array, int pipe_amount)
// {
// 	int i;
// 	int tmp_fdin;
// 	int tmp_fdout;
// 	int pids[pipe_amount];
// 	int pipes[pipe_amount + 1][2]; // create fd's, fd_out[0] - read, fd_in[1] - write;

// 	i = 0;
// 	while (i < pipe_amount + 1)
// 	{
// 		if (pipe(pipes[i]) == -1)
// 		{
// 			printf("ERRROR\n");
// 			exit(0);
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (i < pipe_amount)
// 	{
// 		pids[i] =fork();
// 		if (pids[i] == -1)
// 		{
// 			printf("ERRROR\n");
// 			exit(0);
// 		}
// 		if (pids[i] == 0)
// 		{
// 			int j = 0;
// 			while (j < pipe_amount)
// 			{
// 				if (i != j)
// 					close(pipes[j][0]);
// 				if (i + 1 != j)
// 					close(pipes[j][1]);
// 				j++;
// 			}
// 			char x;
// 			if (read(pipes[i][0], &x, sizeof(int)) == -1)
// 				printf("ERROR\n");
// 			x++;
// 			if (write(pipes[i + 1][1], &x, sizeof(int)) == -1)
// 				printf("ERRROR\n");
// 			close(pipes[i][0]);
// 			close(pipes[i+1][1]);
// 			return (0);
// 		}
// 	}

// 	i = 0;
// 	while (i < pipe_amount)
// 		wait(NULL);
// 	return 0;
// }

void	str_with_pipes(t_all *main_struct, t_list *com_in_str, int pipe_amount)
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
		// handle_pipes(main_struct, array, quant_simple_cmds);
		com_in_str = com_in_str->next;
	}
}
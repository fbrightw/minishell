#include "../../includes/minishell.h"

void	put_input(t_reds *redirs, t_var *var, int *index, int *j)
{
	if (var->words[*index + 1])
	{
		redirs->file_fd = open(var->words[*index + 1], O_RDONLY);
		if (redirs->file_fd < 0) // error
		{
			write(1, var->words[*index + 1], ft_strlen(var->words[*index + 1]));
			write(1, " : ", 3);
			printf("%s\n", strerror(errno));
			var->fl_error = 1;
			redirs->type = -1;
		}
		else
			redirs->type = 0;
		free(var->words[*index]);
		free(var->words[*index + 1]);
		*j += 2;
		*index += 2;
	}
	else
	{
		redirs->type = -1;
		free(var->words[*index]);
		printf("%s\n", strerror(errno));
	}
}

void	put_output(t_reds *redirs, t_var *var, int *index, int *j)
{
	if (var->words[*index + 1])
	{
		if (!var->fl_error)
		{
			redirs->file_fd = open(var->words[*index + 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
			if (redirs->file_fd < 0) // error
			{
				write(1, var->words[*index + 1], ft_strlen(var->words[*index + 1]));
				write(1, " : ", 3);
				printf("%s\n", strerror(errno));
				var->fl_error = 1;
				redirs->type = -1;
			}
			else
				redirs->type = 1;
		}
		free(var->words[*index]);
		free(var->words[*index + 1]);
		*j += 2;
		*index += 2;
	}
	else
	{
		redirs->type = -1;
		free(var->words[*index]);
		printf("%s\n", strerror(errno)); //?
	}
}

void	open_accord_redir(t_in_list *in_inner, t_var *var, int *j, int *index)
{
	t_reds *redirs = malloc(sizeof(t_reds));

	if (!strcmp(var->words[*index], ">"))
	{
		put_output(redirs, var, index, j);
		ft_lstadd_back(&(in_inner->reds_struct), ft_lstnew(redirs));
	}
	else if (!strcmp(var->words[*index], "<"))
	{
		put_input(redirs, var, index, j);
		ft_lstadd_back(&(in_inner->reds_struct), ft_lstnew(redirs));
	}
	else if (!strcmp(var->words[*index], ">>"))
	{
		if (var->words[*index + 1])
		{
			redirs->file_fd = open(var->words[*index + 1], O_CREAT | O_WRONLY | O_APPEND, 0777);
			redirs->type = 2;
			*j += 2;
		}
		else
		{
			redirs->type = -1;
			printf("%s\n", strerror(errno));
		}
		ft_lstadd_back(&(in_inner->reds_struct), ft_lstnew(&redirs));
		free(var->words[*index]);
		if (redirs->type != -1)
			free(var->words[*index + 1]);
	}
}

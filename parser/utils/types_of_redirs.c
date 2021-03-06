#include "../../includes/minishell.h"

void	put_input(t_reds *redirs, t_var *var, int *index, int *j)
{
	if (var->words[*index + 1])
	{
		redirs->file_fd = open(var->words[*index + 1], O_RDONLY);
		if (redirs->file_fd < 0)
			input_error(redirs, var, index);
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
		var->status = 1;
		printf("%s\n", strerror(errno));
	}
}

void	has_filename(t_var *var, t_reds *redirs, int *j, int *index)
{
	if (!var->fl_error)
	{
		redirs->file_fd = open(var->words[*index + 1], \
		O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
		if (redirs->file_fd < 0)
			input_error(redirs, var, index);
		else
			redirs->type = 1;
	}
	free(var->words[*index]);
	free(var->words[*index + 1]);
	*j += 2;
	*index += 2;
}

void	put_output(t_reds *redirs, t_var *var, int *index, int *j)
{
	if (var->words[*index + 1])
		has_filename(var, redirs, j, index);
	else
	{
		redirs->type = -1;
		free(redirs);
		free(var->words[*index]);
		printf("%s\n", strerror(errno));
		var->general->state = errno;
	}
}

void	put_appouput(t_reds *redirs, t_var *var, int *index, int *j)
{
	if (var->words[*index + 1])
	{
		redirs->file_fd = open(var->words[*index + 1], \
		O_CREAT | O_APPEND | O_RDWR, S_IRWXU);
		redirs->type = 2;
		*j += 2;
	}
	else
	{
		redirs->type = -1;
		free(redirs);
		printf("%s\n", strerror(errno));
		var->general->state = errno;
	}
}

void	open_accord_redir(t_in_list *in_inner, t_var *var, int *j, int *index)
{
	t_reds	*redirs;

	redirs = malloc(sizeof(t_reds));
	if (!ft_strcmp(var->words[*index], ">"))
	{
		put_output(redirs, var, index, j);
		ft_lstadd_back(&(in_inner->reds_struct), ft_lstnew(redirs));
	}
	else if (!ft_strcmp(var->words[*index], "<"))
	{
		put_input(redirs, var, index, j);
		ft_lstadd_back(&(in_inner->reds_struct), ft_lstnew(redirs));
	}
	else if (!ft_strcmp(var->words[*index], ">>"))
	{
		put_appouput(redirs, var, index, j);
		ft_lstadd_back(&(in_inner->reds_struct), ft_lstnew(redirs));
		free(var->words[*index]);
		if (redirs->type != -1)
			free(var->words[*index + 1]);
	}
}

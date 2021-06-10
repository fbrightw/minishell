#include "../../includes/minishell.h"

void	free_pipelist(t_list *com_in_str)
{
	t_list	*pipe_lists;

	while (com_in_str)
	{
		pipe_lists = com_in_str->content;
		ft_lstclear(&pipe_lists, free);
		com_in_str = com_in_str->next;
	}
}

void	free_in(t_list *redirs)
{
	while (redirs)
	{
		free((t_reds *)(redirs->content));
		redirs = redirs->next;
	}
}

void	free_in_innerstruct(t_in_list *innerstruct)
{
	int	i;

	i = 0;
	while (innerstruct->args[i])
	{
		free(innerstruct->args[i]);
		i++;
	}
	free(innerstruct->args);
	free(innerstruct);
}

void	free_innerstruct(t_list *com_in_str)
{
	t_list		*pipe_lists;
	t_in_list	*innerstruct;
	t_list		*redirs;

	while (com_in_str)
	{
		pipe_lists = com_in_str->content;
		while (pipe_lists)
		{
			innerstruct = (t_in_list *)(pipe_lists->content);
			redirs = innerstruct->reds_struct;
			free_in(redirs);
			if (ft_lstsize(redirs) > 0)
				ft_lstclear(&redirs, free);
			free_in_innerstruct(innerstruct);
			pipe_lists = pipe_lists->next;
		}
		com_in_str = com_in_str->next;
	}
}

void	cleaning(t_list *com_in_str)
{
	free_innerstruct(com_in_str);
	free_pipelist(com_in_str);
	ft_lstclear(&com_in_str, free);
}

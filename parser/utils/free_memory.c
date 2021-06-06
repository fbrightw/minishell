#include "../../includes/minishell.h"

void	free_pipelist(t_list *com_in_str)
{
	t_list *pipe_lists;

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
		free((t_reds*)(redirs->content));
		redirs = redirs->next;
	}
}

void	free_innerstruct(t_list *com_in_str)
{
	t_list *pipe_lists;
	int i;

	while (com_in_str)
	{
		pipe_lists = com_in_str->content;
		while (pipe_lists)
		{
			t_in_list *innerstruct = (t_in_list*)(pipe_lists->content);
			t_list *redirs = innerstruct->reds_struct;
			free_in(redirs);
			ft_lstclear(&redirs, free);
			i = 0;
			while (innerstruct->args[i])
			{
				free(innerstruct->args[i]);
				i++;
			}
			free(innerstruct->args);
			free(innerstruct);
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

#include "../../includes/minishell.h"

void	return_prev_value_in_list(t_list *history)
{
	char	*changes;
	char	*temp;

	while (history)
	{
		changes = ((t_history *)(history->content))->changes;
		temp = ((t_history *)(history->content))->temp;
		if (changes && strcmp(changes, temp))
		{
			free(changes);
			((t_history *)(history->content))->changes = \
			ft_strdup(((t_history *)(history->content))->temp);
		}
		history = history->next;
	}
}

void	return_prev_his_str(t_list *history)
{
	t_history	*hist_struct;

	while (history)
	{
		hist_struct = (t_history *)((history)->content);
		if (ft_strcmp(hist_struct->changes, hist_struct->temp))
		{
			free(((t_history *)(history->content))->changes);
			hist_struct->changes = ft_strdup(hist_struct->temp);
		}
		history = history->next;
	}
}

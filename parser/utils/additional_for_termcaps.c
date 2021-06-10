#include "../../includes/minishell.h"

t_history	*exact_list(t_list *history, t_var *var)
{
	t_history	*exact_l;
	int			count;

	count = 0;
	exact_l = NULL;
	while (count < (var->numb) - 1)
	{
		history = history->next;
		count++;
	}
	if (history != NULL)
	{
		if (history->content)
			exact_l = ((t_history *)(history->content));
	}
	return (exact_l);
}

void	get_exact_str(t_list *history, t_history **list_struct, int numb)
{
	t_history	*exact_l;
	int			count;

	count = 0;
	while (count < numb - 1)
	{
		history = history->next;
		count++;
	}
	exact_l = (t_history *)(history->content);
	(*list_struct)->temp = ft_strdup(exact_l->changes);
	(*list_struct)->changes = ft_strdup(exact_l->changes);
}

void	prev_hist(t_list *history, t_var *var)
{
	t_history	*hist;
	int			i;

	i = 0;
	while (i < var->numb - 1)
	{
		hist = (t_history *)(history->content);
		printf("%s\n", hist->temp);
		hist->changes = hist->temp;
		history = history->next;
		i++;
	}
	i++;
	while (i < var->quant - 1)
	{
		hist = (t_history *)(history->content);
		hist->changes = hist->temp;
		history = history->next;
		i++;
	}
}

void	return_prev_value_in_list(t_list *history)
{
	char	*changes;
	char	*temp;

	while (history)
	{
		changes = ((t_history *)(history->content))->changes;
		temp = ((t_history *)(history->content))->temp;
		if (changes && ft_strcmp(changes, temp))
		{
			free(changes);
			((t_history *)(history->content))->changes = \
			ft_strdup(((t_history *)(history->content))->temp);
		}
		history = history->next;
	}
}

void	return_prev_his_str(t_list *iter)
{
	t_history	*hist;

	while (iter)
	{
		hist = (t_history *)((iter)->content);
		if (ft_strcmp(hist->changes, hist->temp))
		{
			free(((t_history *)(iter->content))->changes);
			hist->changes = ft_strdup(hist->temp);
		}
		iter = iter->next;
	}
}

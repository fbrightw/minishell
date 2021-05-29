#include "../../includes/minishell.h"

t_history	*exact_list(t_list *history, t_var *var)
{
	int count;
	t_history *exact_l;

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
			exact_l = ((t_history*)(history->content));
	}
	return (exact_l);
}

void	get_exact_str(t_list *history, t_history **list_struct, int numb)
{
	t_history *exact_l;
	int count;

	count = 0;
	while (count < numb - 1)
	{
		history = history->next;
		count++;
	}
	exact_l = (t_history*)(history->content);
	(*list_struct)->temp = ft_strdup(exact_l->changes);
	(*list_struct)->changes = ft_strdup(exact_l->changes);
}

void	prev_hist(t_list *history, t_var *var)
{
	int i;

	i = 0;
	while (i < var->numb - 1)
	{
		printf("%s\n", ((t_history*)(history)->content)->temp);
		((t_history*)(history)->content)->changes = ((t_history*)(history)->content)->temp;
		history = history->next;
		i++;
	}
	i++;
	while (i < var->quant - 1)
	{
		((t_history*)(history)->content)->changes = ((t_history*)(history)->content)->temp;
		history = history->next;
		i++;
	}
}

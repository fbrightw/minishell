#include "../includes/minishell.h"

t_comm	*ft_lstnew_n(char **args)
{
	t_comm *name;

	name = malloc(sizeof(t_comm));
	if (name == 0)
		return (0);
	name->args = args;
	name->next = 0;
	return (name);
}

int		ft_lstsize_n(t_comm *com)
{
	int i;

	i = 0;
	while (com)
	{
		i++;
		com = com->next;
	}
	return (i);
}

t_comm	*ft_lstlast_n(t_comm *com)
{
	int i;

	i = 0;
	i = ft_lstsize_n(com) - 1;
	while (i > 0)
	{
		i--;
		com = com->next;
	}
	return (com);
}

void	ft_lstadd_back_n(t_comm **com, t_comm *new)
{
	t_comm *tmp;

	if (*com != NULL)
	{
		tmp = ft_lstlast_n(*com);
		tmp->next = new;
		new->next = 0;
	}
	else
	{
		new->next = NULL;
		*com = new;
	}
}
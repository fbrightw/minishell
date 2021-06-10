#include "../includes/minishell.h"

char	*not_from_history(t_list **history, t_var *var, t_history **list_struct)
{
	t_history	*hist;
	t_list		*iter;

	if (!g_flag)
	{
		if ((*list_struct)->temp[0] != '\0')
		{
			(*list_struct)->changes = ft_strdup((*list_struct)->temp);
			ft_lstadd_back(history, ft_lstnew(*list_struct));
			iter = *history;
			return_prev_his_str(iter);
			return ((*list_struct)->temp);
		}
	}
	free((*list_struct)->temp);
	free((*list_struct));
	return (NULL);
}

char	*from_hist_wo_sig(t_list *history, t_history **list_struct, t_var *var)
{
	if (exact_list(history, var)->changes[0] != '\0')
	{
		free((*list_struct)->temp);
		(*list_struct)->temp = ft_strdup(exact_list(history, var)->changes);
		(*list_struct)->changes = ft_strdup(exact_list(history, var)->changes);
		if ((*list_struct)->temp[0] != '\0')
		{
			return_prev_value_in_list(history);
			ft_lstadd_back(&history, ft_lstnew(*list_struct));
			return ((*list_struct)->changes);
		}
		return (NULL);
	}
	else
	{
		free(exact_list(history, var)->changes);
		exact_list(history, var)->changes = \
		ft_strdup(exact_list(history, var)->temp);
		free(*list_struct);
		free((*list_struct)->temp);
		return (NULL);
	}
}

char	*from_history(t_list **history, t_var *var, t_history **list_struct)
{
	if (!g_flag)
		return (from_hist_wo_sig(*history, list_struct, var));
	free((*list_struct)->temp);
	free((*list_struct));
	return (NULL);
}

int	strings(t_list **history, t_var *var, t_history **list_struct)
{
	int	l;

	if (!g_flag)
	{
		l = read(0, var->str, 4);
		var->str[l] = '\0';
	}
	else
		return (0);
	if (!ft_strcmp(var->str, "\e[A"))
		up(history, var, list_struct);
	else if (!ft_strcmp(var->str, "\e[B"))
		down(history, var, list_struct);
	else if (*(var->str) == 127)
		backsp(history, var, list_struct);
	else
	{
		if (ft_isprint(var->str[0]))
			word(history, var, list_struct);
	}
	return (1);
}

void	main_while(t_list **history, t_var *var, t_history *list_struct)
{
	while (!g_flag && ft_strcmp(var->str, "\n"))
	{
		if (!ft_strcmp(var->str, "\4"))
		{
			if (list_struct->temp[0] == '\0')
			{
				ft_putstr_fd("\nexit\n", 1);
				exit(var->status);
			}
		}
		if (!strings(history, var, &list_struct))
			break ;
	}
}

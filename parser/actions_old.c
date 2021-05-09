#include "../includes/minishell.h"

int	ft_putchar (int c)
{
	write(1, &c, 1);
	return (1);
}

void	word(t_list **history, t_var *var, t_history **hist)
{
	//write down
	write(1, var->str, 1);
	if (*var->str != '\n' && *var->str != '\4')
	{
		if ((*hist)->numb == (*hist)->quant)
		{
			if ((*hist)->temp[0] != '\0')
				(*hist)->temp = ft_strjoin((*hist)->temp, var->str);
			else
				(*hist)->temp = ft_strdup(var->str);
		}
		else
		{
			if ((*hist)->changes[0] != '\0')
				(*hist)->changes = ft_strjoin((*hist)->changes, var->str);
			else //если меняется история
			{
				(*hist)->changes = ft_strjoin((*hist)->temp, var->str);
				var->change_hist = (*hist)->numb;
			}
		}
	}
}

void	backsp(t_list **history, t_var *var,  t_history **hist)
{
	int len;
	char *temp;

	temp = (*hist)->changes;
	len = 0;
	if ((*hist)->numb == (*hist)->quant)
	{
		if ((*hist)->temp[0] != '\0')
		{
			tputs(tgetstr("le", 0), 1, ft_putchar);
			tputs(tgetstr("dc", 0), 1, ft_putchar);
			len = ft_strlen((*hist)->temp);
			(*hist)->temp = ft_substr((*hist)->temp, 0, len - 1);
		}
	}
	else
	{
		if (var->change_hist == (*hist)->numb)
		{
			tputs(tgetstr("le", 0), 1, ft_putchar);
			tputs(tgetstr("dc", 0), 1, ft_putchar);
			len = ft_strlen((*hist)->changes);
			(*hist)->changes = ft_substr((*hist)->changes, 0, len - 1);
		}
		else
		{
			tputs(tgetstr("le", 0), 1, ft_putchar);
			tputs(tgetstr("dc", 0), 1, ft_putchar);
			len = ft_strlen((*hist)->str);
			(*hist)->str = ft_substr((*hist)->str, 0, len - 1);
			var->fl = 1;
			(*hist)->changes = (*hist)->str;
			var->change_hist = (*hist)->numb;
		}
	}
}

void	down(t_list **history, t_var *var, t_history **hist)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tgetstr("ce", 0), 1, ft_putchar);
	if ((*hist)->numb < (*hist)->quant)
		(*hist)->numb += 1;
	if ((*hist)->numb < (*hist)->quant)
	{
		*hist = exact_list(*history, *hist);
		if (var->change_hist == (*hist)->numb)
			write(1,(*hist)->changes, ft_strlen((*hist)->changes));
		else
			write(1, (*hist)->temp, ft_strlen((*hist)->temp));
			// (*hist)->str = write_lists(*history, *hist, var);
	}
	else
		write(1, (*hist)->temp, ft_strlen((*hist)->temp));
}

void	up(t_list **history, t_var *var, t_history **hist)
{
	if ((*hist)->numb > 0)
		(*hist)->numb -= 1;
	if ((*hist)->numb == (*hist)->quant)
	{
		write(1, (*hist)->temp, ft_strlen((*hist)->temp));
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("ce", 0), 1, ft_putchar); //delete line
	}
	else if ((*hist)->numb != 0)
	{
		*hist = exact_list(*history, *hist);
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("ce", 0), 1, ft_putchar); //delete line
		if (var->change_hist == (*hist)->numb)
			write(1, (*hist)->changes, ft_strlen((*hist)->changes));
		else
			write(1, (*hist)->temp, ft_strlen((*hist)->temp));
			// (*hist)->str = write_lists(*history, *hist, var);
	}
}

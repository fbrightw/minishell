#include "../includes/minishell.h"

int	ft_putchar (int c)
{
	write(1, &c, 1);
	return (1);
}

void	word(t_list **history, t_var *var, t_history **list_struct)
{
	//write down
	t_history *hist;
	write(1, var->str, 1);
	if (*var->str != '\n' && *var->str != '\4')
	{
		if (var->numb == var->quant)
		{
			if (((*list_struct)->temp)[0] != '\0')
				(*list_struct)->temp = ft_strjoin((*list_struct)->temp, var->str);
			else
			{
				// write(1, "YA\n", 3);
				free((*list_struct)->temp);
				(*list_struct)->temp = ft_strdup(var->str);
			}
		}
		else
		{
			hist = exact_list(*history, var);
			hist->changes = ft_strjoin(hist->changes, var->str);
		}
	}
}

void	backsp(t_list **history, t_var *var,  t_history **list_struct)
{
	int len;
	t_history *hist;

	len = 0;
	if (var->numb == var->quant)
	{
		if ((*list_struct)->temp[0] != '\0')
		{
			tputs(tgetstr("le", 0), 1, ft_putchar);
			tputs(tgetstr("dc", 0), 1, ft_putchar);
			len = ft_strlen((*list_struct)->temp);
			(*list_struct)->temp = ft_substr((*list_struct)->temp, 0, len - 1);
		}
	}
	else
	{
		hist = exact_list(*history, var);
		if (hist && hist->changes[0] != '\0')
		{
			tputs(tgetstr("le", 0), 1, ft_putchar);
			tputs(tgetstr("dc", 0), 1, ft_putchar);
			len = ft_strlen(hist->changes);
			hist->changes = ft_substr(hist->changes, 0, len - 1);
		}
	}
}

void	down(t_list **history, t_var *var, t_history **list_struct)
{
	t_history *hist;
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tgetstr("ce", 0), 1, ft_putchar);

	if (var->numb < var->quant)
		var->numb += 1;
	if (var->numb < var->quant)
		hist = exact_list(*history, var);
	if (var->numb < var->quant)
		write(1,(hist)->changes, ft_strlen((hist)->changes));
	else
		write(1, (*list_struct)->temp, ft_strlen((*list_struct)->temp));
}

void	up(t_list **history, t_var *var, t_history **list_struct)
{
	t_history *hist;
	if (var->numb > 1)
		var->numb -= 1;
	if (var->numb > 0)
		hist = exact_list(*history, var);
	if (var->numb == var->quant)
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("ce", 0), 1, ft_putchar); //delete line
		write(1, (*list_struct)->temp, ft_strlen((*list_struct)->temp));
	}
	else
	{
		// write(1, "YA\n", 3);
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("ce", 0), 1, ft_putchar); //delete line
		write(1, (hist)->changes, ft_strlen((hist)->changes));
	}
}

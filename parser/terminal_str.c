#include "../includes/minishell.h"

t_history	*exact_list(t_list *history, t_var *var)
{
	int count;

	count = 0;
	t_history *exact_l;

	while (count < (var->numb) - 1)
	{
		history = history->next;
		count++;
	}
	exact_l = ((t_history*)(history->content));
	return (exact_l);
}

void	strings(t_list **history, t_var *var,  t_history **hist)
{
	int l;

	l = read(0, var->str, 100);
	var->str[l] = '\0';
	if (!strcmp(var->str, "\e[A"))
		up(history, var, hist);
	else if (!strcmp(var->str, "\e[B"))
		down(history, var, hist);
	else if (*(var->str) == 127)
		backsp(history, var, hist);
	else
		word(history, var, hist);
}

void	termcaps(struct termios term, t_var *var, t_all *main_struct)
{
	var->term_name = find_variable_in_env(main_struct, "TERM", 0); //xterm-256color  (каждый)
	tcgetattr(0, &term); //возвращает инфу по открытому fd, связанному с терминалом {считываем текущий режим работы терминала}
	term.c_lflag &= ~(ECHO); //включен режим отображения
	term.c_lflag &= ~(ICANON); //ввод в каноническом виде
	tcsetattr(0, TCSANOW, &term); //устанавливает атрибуты терминала, ассоциированного с fd.
	tgetent(0, var->term_name);
	ft_putstr_fd("\e[32m minishell \e[0m", 1);
	tputs(save_cursor, 1, ft_putchar);
	free(var->term_name);
}

void	return_value(t_list **history, t_var *var, int numb)
{
	int i;
	char *change;
	char *temp;

	i = 0;
	while (i < numb)
	{
		*history = (*history)->next;
		change = ((t_history *)(*history)->content)->changes;
		temp = ((t_history *)(*history)->content)->temp;
		change = ft_strdup(temp);
		i++;
	}
	i++;
	*history = (*history)->next;
	while (i < var->quant)
	{
		*history = (*history)->next;
		change = ((t_history *)(*history)->content)->changes;
		temp = ((t_history *)(*history)->content)->temp;
		change = ft_strdup(temp);
		i++;
	}
}

void	get_exact_str(t_list *history, t_history **list_struct, int numb)
{
	int count;

	count = 0;
	t_history *exact_l;
	while (count < numb - 1)
	{
		history = history->next;
		count++;
	}
	exact_l = (t_history*)(history->content);
	(*list_struct)->temp = ft_strdup(exact_l->changes);
	(*list_struct)->changes = ft_strdup((*list_struct)->temp);
}

void	prev_hist(t_list *history, t_var *var)
{
	int i;

	i = 0;
	while (i < var->numb)
	{
		((t_history*)(history)->content)->changes = ((t_history*)(history)->content)->temp;
		history = history->next;
		i++;
	}
	i++;
	while (i < var->quant)
	{
		((t_history*)(history)->content)->changes = ((t_history*)(history)->content)->temp;
		(history) = (history)->next;
		i++;
	}
}

char	*save_history_in_lists(t_list **history, t_all *main_struct, t_var *var)
{
	struct termios term;
	t_history *list_struct;

	var->str[0] = '\0';

	list_struct = malloc(sizeof(t_history));
	list_struct->temp = malloc(sizeof(char));
	list_struct->changes = NULL;
	list_struct->temp[0] = '\0';

	// termcaps
	termcaps(term, var, main_struct);

	var->quant = ft_lstsize(*history) + 1;
	var->numb = var->quant;

	// the main loop
	while (strcmp(var->str, "\n") && strcmp(var->str, "\4"))
		strings(history, var, &list_struct);

	if (var->numb == var->quant)
	{
		if (list_struct->temp[0] != '\0')
		{
			list_struct->changes = ft_strdup(list_struct->temp);
			ft_lstadd_back(history, ft_lstnew(list_struct));
			prev_hist(*history, var);
			// t_list *iter = *history;
			// while (iter)
			// {
			// 	printf("%s\n", ((t_history*)(iter->content))->changes);
			// 	iter = iter->next;
			// }
			return(list_struct->temp);
		}
	}
	else if (var->numb != 0)
	{
		if (exact_list(*history, var)->changes[0] != '\0')
		{
			get_exact_str(*history, &list_struct, var->numb);
			if (list_struct->temp[0] != '\0')
			{
				prev_hist(*history, var);
				ft_lstadd_back(history, ft_lstnew(list_struct));
				return(list_struct->changes);
			}
		}
		return (list_struct->temp);
	}
}

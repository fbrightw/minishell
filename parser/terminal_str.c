#include "../includes/minishell.h"

void	strings(t_list **history, t_var *var,  t_history **list_struct)
{
	int l;

	l = read(0, var->str, 4); //close l
	var->str[l] = '\0';
	if (!strcmp(var->str, "\e[A"))
		up(history, var, list_struct);
	else if (!strcmp(var->str, "\e[B"))
		down(history, var, list_struct);
	else if (*(var->str) == 127)
		backsp(history, var, list_struct);
	else
	{
		if (ft_isprint(*(var->str)))
			word(history, var, list_struct);
		else
			write(1, "\n", 1);
	}
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

char	*not_from_history(t_list **history,t_var *var, t_history **list_struct)
{
	if ((*list_struct)->temp[0] != '\0')
	{
		(*list_struct)->changes = ft_strdup((*list_struct)->temp); // change = temp = qwe
		ft_lstadd_back(history, ft_lstnew(*list_struct));
		t_list *iter = *history;
		while (iter)
		{
			if (strcmp(((t_history*)((iter)->content))->changes, ((t_history*)((iter)->content))->temp))
			{
				free(((t_history*)(iter->content))->changes);
				((t_history*)(iter->content))->changes = ft_strdup(((t_history*)(iter->content))->temp);
			}
			iter = iter->next;
		}
		// print(history);
		return((*list_struct)->temp);
	}
	// print(history);
	free((*list_struct));
	return (NULL);
}

char	*from_history(t_list **history,t_var *var, t_history **list_struct)
{
	if (exact_list(*history, var)->changes[0] != '\0')
	{
		free((*list_struct)->temp);
		(*list_struct)->temp = ft_strdup(exact_list(*history, var)->changes);
		(*list_struct)->changes = ft_strdup(exact_list(*history, var)->changes);
		if ((*list_struct)->temp[0] != '\0')
		{
			t_list *iter = *history;
			while (iter)
			{
				if (((t_history*)(iter->content))->changes && strcmp(((t_history*)((iter)->content))->changes, ((t_history*)((iter)->content))->temp))
				{
					free(((t_history*)(iter->content))->changes);
					((t_history*)(iter->content))->changes = ft_strdup(((t_history*)(iter->content))->temp);
				}
				iter = iter->next;
			}
			ft_lstadd_back(history, ft_lstnew(*list_struct));
			// print(history);
			return((*list_struct)->changes);
		}
		return (NULL);
	}
	else
	{
		free(exact_list(*history, var)->changes);
		exact_list(*history, var)->changes = ft_strdup(exact_list(*history, var)->temp);
		free(*list_struct);
		free((*list_struct)->temp);
		return (NULL);
	}
	// print(history);
}

char	*save_history_in_lists(t_list **history, t_all *main_struct, t_var *var)
{
	struct termios term;
	t_history *list_struct;

	var->str[0] = '\0';

	list_struct = malloc(sizeof(t_history));
	list_struct->temp = malloc(sizeof(char));
	list_struct->changes =  NULL;
	list_struct->temp[0] = '\0';

	// termcaps
	termcaps(term, var, main_struct);
	var->quant = ft_lstsize(*history) + 1;
	var->numb = var->quant;

	// the main loop
	while (strcmp(var->str, "\n") && strcmp(var->str, "\4"))
		strings(history, var, &list_struct);

	if (var->numb == var->quant)
		return(not_from_history(history, var, &list_struct));
	else
		return(from_history(history, var, &list_struct));
}

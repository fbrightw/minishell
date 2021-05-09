#include "../includes/minishell.h"

char	*write_lists(t_list *history, t_history *hist, t_var *var)
{
	int count;
	char *temp;
	char *str = malloc(sizeof(char));

	count = 0;
	while (count < (hist->numb) - 1)
	{
		history = history->next;
		count++;
	}
	if (history != NULL)
	{
		str = ((t_history *)(history)->content)->temp;
		write(1, str, ft_strlen(str));
		temp = ft_strdup(str);
	}
	var->save_numb = hist->numb;
	return (temp);
}

t_history	*exact_list(t_list *history, t_history *hist)
{
	int count;

	count = 0;
	while (count < (hist->numb) - 1)
	{
		history = history->next;
		count++;
	}
	return (history->content);
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

char	*save_history_in_lists(t_list **history, t_all *main_struct, t_var	*var)
{
	struct termios term;
	t_history *hist;
	t_history *before;
	hist = malloc(sizeof(t_history));
	hist->temp = malloc(sizeof(char));
	hist->changes = malloc(sizeof(char));
	hist->str = malloc(sizeof(char));
	hist->temp[0] = '\0';
	var->str[0] = '\0';

	hist->quant = ft_lstsize(*history) + 1;
	hist->numb = hist->quant;
	var->temporary = malloc(sizeof(char));
	var->save_numb = -1;
	var->change_hist = -1;
	var->fl = 0;

 // termcaps
	termcaps(term, var, main_struct);

// the main loop
	while (strcmp(var->str, "\n") && strcmp(var->str, "\4"))
		strings(history, var, &hist);

	// add_into_list(temp);
	ft_lstadd_back(history, ft_lstnew(hist));
	if (hist->numb == hist->quant)
		return(hist->temp);
	else
		return(hist->changes);
}

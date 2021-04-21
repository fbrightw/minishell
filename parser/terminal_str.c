#include "../includes/minishell.h"

int	ft_putchar (int c)
{
	write(1, &c, 1);
	return (1);
}

void	write_lists(t_list *history, int numb)
{
	int count;

	count = 0;
	while (count < numb - 1)
	{
		history = history->next;
		count++;
	}

	if (history != NULL)
		write(1, history->content, ft_strlen(history->content));
}

void	continue_of_func(int l, char *str, char **buf)
{
	if (!strcmp(str, "\177"))
	{
		tputs(tgetstr("le", 0), 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
	}
	else
	{
		if (*buf == 0)
		{
			*buf = ft_strdup(str);
			write(1, *buf, 1);
		}
		else
		{
			*buf = ft_strjoin(*buf, str); //leaks
			write(1, str, l);
		}
	}
}

void	strings(char *str, int *numb, t_list **history, char **buf)
{
	int l;

	l = read(0, str, 100);
	if (!strcmp(str, "\e[A"))
	{
		if (*numb != 0)
		{
			*numb -= 1;
			tputs(restore_cursor, 1, ft_putchar);
			tputs(tgetstr("ce", 0), 1, ft_putchar); //delete line
			write_lists(*history, *numb);
			// tputs(save_cursor, 1, ft_putchar);
		}
		else
			tputs(restore_cursor, 1, ft_putchar);
	}
	else if (!strcmp(str, "\e[B"))
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("ce", 0), 1, ft_putchar);
		if (*numb < ft_lstsize(*history) + 1)
		{
			*numb += 1;
			write_lists(*history, *numb);
		}
		tputs(restore_cursor, 1, ft_putchar);
	}
	continue_of_func(l, str, buf);
}

void	save_history_in_lists(t_list **history)
{
	char str[2000];
	int l;
	int numb;
	char *buf;
	struct termios term;
	char *term_name = "xterm-256color";

	numb = ft_lstsize(*history) + 1;
	buf = NULL;
	tcgetattr(0, &term); //возвращает инфу по открытому fd, связанному с терминалом {считываем текущий режим работы терминала}
	term.c_lflag &= ~(ECHO); //включен режим отображения
	term.c_lflag &= ~(ICANON); //ввод в каноническом виде
	tcsetattr(0, TCSANOW, &term); //устанавливает атрибуты терминала, ассоциированного с fd.
	tgetent(0, term_name);
	ft_putstr_fd("\e[32m minishell \e[0m", 1);
	tputs(save_cursor, 1, ft_putchar);
	strings(str, &numb, history, &buf);
	while (strcmp(str, "\n") && strcmp(str, "\4"))
		strings(str, &numb, history, &buf);
	ft_lstadd_back(history, ft_lstnew(buf));
	split_into_commands(history, &buf);
}

int main()
{
	t_list *history;

	history = NULL;
	while (1)
		save_history_in_lists(&history);
}

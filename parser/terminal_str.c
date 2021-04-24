#include "../includes/minishell.h"

int	ft_putchar (int c)
{
	write(1, &c, 1);
	return (1);
}

void	write_lists(t_list *history, int numb, char **buf)
{
	int count;

	count = 0;
	while (count < numb - 1)
	{
		history = history->next;
		count++;
	}

	if (history != NULL)
	{
		write(1, history->content, ft_strlen(history->content));
		*buf = history->content;
	}
}

void	continue_of_func(t_list **history, int l, char *str, char **buf)
{
	char *new_buf;
	int len;

	new_buf = NULL;
	if (*str == 127)
	{
		tputs(tgetstr("le", 0), 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		len = ft_strlen(*buf);
		new_buf = ft_substr(*buf, 0, len - 1);
		*buf = new_buf;
	}
	else
	{
		write(1, str, l);
		if (*str != '\n' && *str != '\4')
		{
			if (*buf == 0)
				*buf = ft_strdup(str);
			else
				*buf = ft_strjoin(*buf, str); //leaks
		}
	}
}

void	strings(char *str, int *numb, t_list **history, char **buf)
{
	int l;

	l = read(0, str, 100);
	str[l] = '\0';
	if (!strcmp(str, "\e[A"))
	{
		if (*numb != 0)
		{
			*numb -= 1;
			tputs(restore_cursor, 1, ft_putchar);
			tputs(tgetstr("ce", 0), 1, ft_putchar); //delete line
			write_lists(*history, *numb, buf);
		}
	}
	else if (!strcmp(str, "\e[B"))
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("ce", 0), 1, ft_putchar);
		if (*numb < ft_lstsize(*history) + 1)
		{
			*numb += 1;
			write_lists(*history, *numb, buf);
		}
	}
	else
		continue_of_func(history, l, str, buf);
}

char	*save_history_in_lists(t_list **history, t_all *main_struct)
{
	char str[200];
	int numb;
	char *buf;
	struct termios term;
	char *term_name = "xterm-256color";

	numb = ft_lstsize(*history) + 1;
	buf = NULL;
	str[0] = '\0';
	tcgetattr(0, &term); //возвращает инфу по открытому fd, связанному с терминалом {считываем текущий режим работы терминала}
	term.c_lflag &= ~(ECHO); //включен режим отображения
	term.c_lflag &= ~(ICANON); //ввод в каноническом виде
	tcsetattr(0, TCSANOW, &term); //устанавливает атрибуты терминала, ассоциированного с fd.
	tgetent(0, term_name);
	ft_putstr_fd("\e[32m minishell \e[0m", 1);
	tputs(save_cursor, 1, ft_putchar);
	while (strcmp(str, "\n") && strcmp(str, "\4"))
		strings(str, &numb, history, &buf);
	ft_lstadd_back(history, ft_lstnew(buf));
	return (buf);
}

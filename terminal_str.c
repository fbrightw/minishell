#include "minishell.h"
#include <string.h>

int	ft_putchar (int c)
{
	write(1, &c, 1);
	return (1);
}

void	write_prev(t_list *history, int numb)
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

void	first(char *str, int numb, t_list **history, char *buf)
{
	if (!strcmp(str, "\e[A"))
	{
		if (numb != 0)
		{
			numb -= 1;
			tputs(restore_cursor, 1, ft_putchar);
			tputs(tgetstr("ce", 0), 1, ft_putchar); //delete line
			write_prev(*history, numb);
			// write(1, "prev", 4);
		}
	}
	else if (!strcmp(str, "\e[B"))
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("ce", 0), 1, ft_putchar);
		write(1, "next", 4);
	}
	else if (!strcmp(str, "\177"))
	{
		tputs(tgetstr("le", 0), 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
	}
	else
	{
		buf = ft_strdup(str);
		write(1, buf, 1);
	}
}
char	*save_history_in_lists(t_list **history)
{
	char str[2000];
	char	*buf;
	int l;
	int numb;
	struct termios term;
	char *term_name = "xterm-256color";

	numb = ft_lstsize(*history) + 1;
	tcgetattr(0, &term); //возвращает инфу по открытому fd, связанному с терминалом {считываем текущий режим работы терминала}
	term.c_lflag &= ~(ECHO); //включен режим отображения
	term.c_lflag &= ~(ICANON); //ввод в каноническом виде
	tcsetattr(0, TCSANOW, &term); //устанавливает атрибуты терминала, ассоциированного с fd.
	tgetent(0, term_name);
	ft_putstr_fd("\e[32m minishell \e[0m", 1);
	tputs(save_cursor, 1, ft_putchar);
	buf = NULL;
	l = read(0, str, 100);
	first(str, numb, history, buf);
	while (strcmp(str, "\n") && strcmp(str, "\4"))
	{
		l = read(0, str, 100);
		if (!strcmp(str, "\e[A"))
		{
			if (numb != 0)
			{
				numb -= 1;
				tputs(restore_cursor, 1, ft_putchar);
				tputs(tgetstr("ce", 0), 1, ft_putchar); //delete line
				write_prev(*history, numb);
			}
		}
		else if (!strcmp(str, "\e[B"))
		{
			tputs(restore_cursor, 1, ft_putchar);
			tputs(tgetstr("ce", 0), 1, ft_putchar);
			write(1, "next", 4);
		}
		else if (!strcmp(str, "\177"))
		{
			tputs(tgetstr("le", 0), 1, ft_putchar);
			tputs(tgetstr("dc", 0), 1, ft_putchar);
		}
		else
		{
			if (buf == 0)
			{
				buf = ft_strdup(str);
				write(1, buf, 1);
			}
			else
			{
				buf = ft_strjoin(buf, str); //leaks
				write(1, str, l);
			}
		}
	}
	// int k = 0;
	// while (k < ft_strlen(buf))
	// {
	// 	// if (buf[k] == '\n')
	// 	// 	printf("YES");
	// 	printf("%c\n", buf[k]);
	// 	k++;
	// }
	// printf("%zu\n", ft_strlen(buf));
	ft_lstadd_back(history, ft_lstnew(buf));
	return (buf);
}

int main()
{
	char *line;
	t_list *history;

	history = NULL;
	while (1)
		line = save_history_in_lists(&history);
}

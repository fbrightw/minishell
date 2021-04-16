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
	while (count < numb)
	{
		history = history->next;
		count++;
	}
	printf("%s\n", history->content);
}

char	*save_history_in_lists(void)
{
	char str[2000];
	int l;
	int numb;
	struct termios term;
	t_list history;
	history.content = 0;
	char *term_name = "xterm-256color";
	tcgetattr(0, &term); //возвращает инфу по открытому fd, связанному с терминалом {считываем текущий режим работы терминала}
	term.c_lflag &= ~(ECHO); //включен режим отображения
	term.c_lflag &= ~(ICANON); //ввод в каноническом виде
	tcsetattr(0, TCSANOW, &term); //устанавливает атрибуты терминала, ассоциированного с fd.
	tgetent(0, term_name);
	ft_putstr_fd("\e[32m minishell \e[0m", 1);
	tputs(save_cursor, 1, ft_putchar);
	do
		{
			l = read(0, str, 100);
			if (!strcmp(str, "\e[A"))
			{
				tputs(restore_cursor, 1, ft_putchar);
				tputs(tgetstr("ce", 0), 1, ft_putchar); //delete line
				// write_prev(&history, numb);
				write(1, "prev", 4);
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
				if (history.content == 0)
					history.content = ft_strdup(str);
				else
				{
					history.content = ft_strjoin(history.content, str);
					write(1, str, l);
				}
			}
		} while (strcmp(str, "\n") && strcmp(str, "\4"));
	return (history.content);
}

int main()
{
	char *line;

	line = save_history_in_lists();
	// printf("%s\n", line);
}
#include "includes/minishell.h"
#include "execution/builtins/builtins.h"

void	termcaps(t_var *var, struct termios *term, struct termios *term1)
{
	var->term_name = find_variable_in_env(var->general, "TERM", 0); //xterm-256color
	tcgetattr(0, term1);
	tcgetattr(0, term); //возвращает инфу по открытому fd, связанному с терминалом {считываем текущий режим работы терминала}
	term->c_lflag &= ~(ECHO); //включен режим отображения
	term->c_lflag &= ~(ICANON); //ввод в каноническом виде
}

int	main(int argc, char *argv[], char *env[])
{
	t_list *history;
	struct termios term;
	struct termios term1;
	t_var	var;
	t_env	s_env;
	char *str;
	char *builtins[7] = {"echo", "cd", "pwd", "export", "nst", "env", "exit"};
	var.builtins = builtins;

	history = NULL;
	set_env(&s_env, env); // <- Закидываю переменные окружения в новый двумерный массив
	var.general = malloc(sizeof(t_all));
	var.general->env = s_env.env_arr;
	var.general->f_env = s_env;
	termcaps(&var, &term, &term1);
	while (1)
	{
		str = save_history_in_lists(&history, &var, term);
		if (str)
			split_into_commands(str, &var, term1);
		tputs(save_cursor, 1, ft_putchar);
	}
}

#include "includes/minishell.h"

void	termcaps(t_var *var, struct termios *term, struct termios *term1)
{
	var->term_name = find_variable_in_env(var->general, "TERM", 0); //xterm-256color
	tcgetattr(0, term1);
	tcgetattr(0, term); //возвращает инфу по открытому fd, связанному с терминалом {считываем текущий режим работы терминала}
	term->c_lflag &= ~(ECHO); //включен режим отображения
	term->c_lflag &= ~(ICANON); //ввод в каноническом виде
}

// void	handle_signal_slash(int c)
// {
// 	SIGQUIT;
// }

// void	handle_signal_c(int c)
// {
		// if (c != SIGINT)
			// return ;
		// else
// }

int	main(int argc, char *argv[], char *env[])
{
	t_list *history;
	struct termios term;
	struct termios term1;
	t_var	var;
	t_env	s_env;
	char *str;
	char *builtins[7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	var.builtins = builtins;

	//signal(SIGQUIT, func);//ctrl+/
	//signal(SIGINT, func2); //ctrl+c
	history = NULL;
	set_env(var.general, &s_env, env); // <- Закидываю переменные окружения в новый двумерный массив
	var.general = malloc(sizeof(t_all));
	var.general->envs = &s_env;
	// var.general->envs->env_arr = s_env.env_arr;
	// int i = 0;
	// while (var.general->envs->env_arr[i])
	// {
	// 	printf("%s\n", var.general->envs->env_arr[i]);
	// 	i++;
	// }
	termcaps(&var, &term, &term1);
	while (1)
	{
		str = save_history_in_lists(&history, &var, term);
		if (str)
			split_into_commands(str, &var, term1);
		tputs(save_cursor, 1, ft_putchar);
	}
}

#include "includes/minishell.h"
#include "execution/builtins/builtins.h"

int	main(int argc, char *argv[], char *env[])
{
	t_list *history;
	char *str;
	t_all main_struct;
	t_var	var;
	t_env	s_env;
	char *builtins[7] = {"echo", "cd", "pwd", "export", "nst", "env", "exit"};
	var.builtins = builtins;

	history = NULL;
	set_env(&s_env, env); // <- Закидываю переменные окружения в новый двумерный массив
	main_struct.env = s_env.env_arr;
	main_struct.envs = s_env;

	while (1)
	{
		str = save_history_in_lists(&history, &main_struct, &var); //нужны доработки (leaks)
		printf("sentence = %s\n", str);
		if (str)
			split_into_commands(str, &main_struct, &var);
	}
}

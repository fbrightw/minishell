#include "includes/minishell.h"

void	termcaps(t_var *var, struct termios *term, struct termios *term1)
{
	var->status = 0;
	var->term_name = getenv("TERM");
	tcgetattr(0, term1);
	tcgetattr(0, term);
	term->c_lflag &= ~(ECHO);
	term->c_lflag &= ~(ICANON);
	term->c_cc[VMIN] = 0;
	term->c_cc[VTIME] = 1;
}

void	handle_signal_slash(int sig)
{
	(void)(sig);
}

void	handle_signal_c(int sig)
{
	if (sig == 2)
		g_flag = 1;
}

int	main(int argc, char *argv[], char *env[])
{
	struct termios	term;
	struct termios	term1;
	t_list			*history;
	t_var			var;
	t_env			s_env;

	signal(SIGQUIT, handle_signal_slash);
	signal(SIGINT, handle_signal_c);
	history = NULL;
	set_env(var.general, &s_env, env);
	var.general = malloc(sizeof(t_all));
	var.general->envs = &s_env;
	termcaps(&var, &term, &term1);
	while (1)
	{
		g_flag = 0;
		ft_memset(var.str, 0, 200);
		var.term_str = save_history_in_lists(&history, &var, term);
		if (var.term_str && !g_flag)
			split_into_commands(var.term_str, &var, term1);
		tputs(save_cursor, 1, ft_putchar);
	}
}

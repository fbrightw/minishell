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

void	define(t_list *history, t_history **list_struct, \
			t_var *var, struct termios term)
{
	var->str[0] = '\0';
	(*list_struct) = malloc(sizeof(t_history));
	(*list_struct)->temp = malloc(sizeof(char));
	(*list_struct)->changes = NULL;
	(*list_struct)->temp[0] = '\0';
	var->quant = ft_lstsize(history) + 1;
	var->numb = var->quant;
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, var->term_name);
	ft_putstr_fd("\e[32m minishell \e[0m", 1);
	tputs(save_cursor, 1, ft_putchar);
}

char	*save_history_in_lists(t_list **history, t_var *var, \
struct termios term)
{
	t_history	*list_struct;

	var->syntax_fl = 0;
	define(*history, &list_struct, var, term);
	main_while(history, var, list_struct);
	if (!strcmp(var->str, "\n"))
		write(1, "\n", 1);
	if (g_flag)
		write(1, "\n", 1);
	if (var->numb == var->quant)
		return (not_from_history(history, var, &list_struct));
	else
		return (from_history(history, var, &list_struct));
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
		var.term_str = save_history_in_lists(&history, &var, term);
		if (var.term_str && !g_flag)
		{
			tcsetattr(0, TCSANOW, &term1);
			var.fl = 0;
			split_into_commands(var.term_str, &var);
		}
		tputs(save_cursor, 1, ft_putchar);
	}
}

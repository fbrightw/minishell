#include "../../includes/minishell.h"

// This function can do two things:
// 1) NULL -> (str), errno -> (is_errno)				- if system error
// 2) your own custome error -> (str), 0 -> (is_errno)  - if your own error

void	error_msg(char *str, int is_errno, t_all *main_struct, int new_state)
{
	main_struct->state = new_state;
	write(2, COLOR_RED, 5);
	write(2, "error: ", 8);
	if (is_errno)
		write(2, strerror(is_errno), ft_strlen(strerror(is_errno)));
	else if (str)
		write(2, str, ft_strlen(str));
	else
		write(2, "undefined error", 16);
	write(2, COLOR_RESET, 4);
	write(2, "\n", 1);
}

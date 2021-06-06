#include "../../includes/minishell.h"

int	ft_exit(t_all *main_struct, char **arr)
{
	int arr_len;

	arr_len = get_arr_len(arr);
	if (arr_len == 1)
		exit(main_struct->state);
	if (!ft_isnum(arr[1]))
	{
		error_msg("numeric argument required", 0, main_struct, 2);
		exit(2);
	}
	if (arr_len > 2)
	{
		error_msg("too many arguments", 0, main_struct, 1);
		exit(1);
	}
	exit(ft_atoi(arr[1]));
	return (0);
}

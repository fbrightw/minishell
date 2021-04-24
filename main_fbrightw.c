#include "includes/minishell.h"

int main()
{
	t_list *history;
	char *str;
	t_all main_struct;

	history = NULL;
	while (1)
	{
		str = save_history_in_lists(&history, &main_struct);
		split_into_commands(&history, &str, &main_struct);
	}
}

# ifndef MINISHELL_H
# define MINISHELL_H

#include <term.h>
#include <unistd.h>
#include <stdio.h>
#include "../libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <string.h>

typedef struct		s_all
{
	char			**args;
}					t_all;

typedef struct		s_comm
{
	char			**args; //for execve
	struct s_comm	*next;
}					t_comm;

void	save_history_in_lists(t_list **history, t_all *main_struct);
void	split_into_commands(t_list **history, char **buf, t_all *main_struct);
void	ft_lstadd_back_n(t_comm **com, t_comm *new);
t_comm	*ft_lstnew_n(char **args);

#endif
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

#include <sys/types.h>
#include <sys/wait.h>

#include "../execution/builtins/builtins.h"


#define STDOUT
#define STDIN

typedef struct		s_all
{
	char			**args;
	char			**env;
	int				std_fd[2];
	t_env			envs;
}					t_all;

typedef	struct		s_history
{
	char			*str;
	char			*changes;
	char			*temp;
}					t_history;

typedef	struct		s_into_lists
{
	char			**args;
	char			*pipes;
	char			*redirs;
}					t_into_lists;

typedef	struct		s_var
{
	char			*term_name;
	int				numb;
	int				quant;
	char			str[200];
	char 			temp[2];
	char 			**builtins;

}					t_var;

// #include "../execution/work_it/analysis.h"

char	*save_history_in_lists(t_list **history, t_all *main_struct, t_var	*var);
void	word(t_list **history, t_var *var,  t_history **hist);
void	backsp(t_list **history, t_var *var,  t_history **hist);
void	down(t_list **history, t_var *var,  t_history **hist);
void	up(t_list **history, t_var *var,  t_history **hist);
int		ft_putchar (int c);
char	*write_lists(t_list *history, t_history *hist, t_var *var);
void	split_into_commands(char *term_str, t_all *main_struct, t_var	*var);
char	**alloc_mem_for_word(char **com, int k, char *fin_str);
char	**spec_symbols(t_all *main_struct, char **com, char **buf, int k);
char	*find_variable_in_env(t_all *main_struct, char *varible, int fl_to_free);
char	*deal_with_spec_smbls(t_list *com_in_str, t_all *main_struct, t_var *var, char *word);

t_history	*exact_list(t_list *history, t_var *var);
void	get_exact_str(t_list *history, t_history **list_struct, int numb);
void	prev_hist(t_list *history, t_var *var);

// анализ спец символов
// int		cmp_to_symb(char *symbols, char c);
char	*deal_with_spec_smbls(t_list *com_in_str, t_all *main_struct, t_var *var, char *word);
int		find_exact_symb(char *symbols, char c);
int		symbols(char *sym, char *word);
void	dollar_in_quot(char **word, t_all *main_struct, char **command);
void	dollar(char **word, t_all *main_struct, t_var *var, char **command);
void	single_quotes(char **word, t_all *main_struct, t_var *var, char **command);
void	quit_error(char *str);
void	building_word(char **str1, char *str2);
void	backslash(char **word, char **command, t_var *var);

void	indexes_of_pipe_red(t_into_lists *vars);


int		check_if_pipe(char *final_str);
void	str_with_pipes(t_all *main_struct, t_list *com_in_str, int pipe_amount);
void	count_pipes(t_list *com_in_str, int *pipe_amount);
void	ft_split_pipes(t_into_lists *vars, char *final_str, char c, int *k);

void	func(t_list *com_in_str, t_all *main_struct, t_var	*var, char *token);
void	other_command(char **args, char *token, t_all *main_struct);
// void	str_with_pipes(t_list *com_in_str, int pipe_amount);


void	redirs(t_list *com_in_str, t_into_lists *vars, t_all *main_struct, t_var *var);
#endif
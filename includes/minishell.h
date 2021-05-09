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

#include "../execution/builtins/builtins.h"

typedef struct		s_all
{
	char			**args;
	char			**env;
	t_env			envs;
}					t_all;

typedef struct		s_put
{
	char			*str;
	int				act;
	int				numb;
}					t_put;

typedef	struct		s_history
{
	char			*str;
	char			*changes;
	char			*temp;
}					t_history;

typedef	struct		s_into_lists
{
	// char			**before_changes;
	char			**args;
	// char			*status;
}					t_into_lists;

typedef	struct		s_var
{
	char			*term_str;
	char			*term_name;
	int				numb;
	int				quant;
	char			str[200];
	char 			temp[2];
	int				fl;
	int				quot;
	int				save_numb;
	int				change_hist;
	char			*temporary;
	char 			**builtins;
	char			*origin_com;

}					t_var;

#include "../execution/work_it/analysis.h"

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
void	is_it_com(t_list **com_in_str, t_all *main_struct, t_var	*var);
t_history	*exact_list(t_list *history, t_var *var);

// анализ спец символов
int		cmp_to_symb(char *symbols, char c);
int	symbols(char *sym, char *word);
void	dollar_in_quot(char **word, t_all *main_struct, char **command);
void	dollar(char **word, t_all *main_struct, t_var *var, char **command);
void	single_quotes(char **word, t_all *main_struct, t_var *var, char **command);
void	quit_error(char *str);

#endif
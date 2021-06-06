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
#include <signal.h>
# include <errno.h>
# include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

int g_flag;

#define STDOUT 1
#define STDIN 0

#define INPUT '<'
#define OUTPUT '>'
#define APP_OUTPUT ">>"

# define COLOR_RED "\x1b[31m"
# define COLOR_RESET "\x1b[0m"

typedef struct		s_exec
{
	char			**array_of_path;
	char			*to_token;
	char			*path_with_cmd;
}					t_exec;

typedef struct		s_reds
{
	int				type;
	int				file_fd;
}					t_reds;

typedef struct s_in_list
{
	char			**args;
	int				pipe_numb;
	t_list			*reds_struct;
}				t_in_list;

typedef struct		s_env
{
	char			*home;
	char			**env_arr;
}					t_env;

typedef struct		s_all
{
	char			**vars;
	int				state;
	t_env			*envs;
}					t_all;

typedef	struct		s_history
{
	char			*str;
	char			*changes;
	char			*temp;
}					t_history;

typedef	struct		s_var
{
	int				stdout;
	int				stdin;
	char			*term_str;
	char			*term_name;
	int				pipe_amount;
	char			*token;
	int				numb;
	int				quant;
	char			str[200];
	char 			temp[2];
	char			*word;
	char			**words;
	char			*path;
	int				status;
	int				fl_error;
	t_all			*general;
}					t_var;

char	*save_history_in_lists(t_list **history, t_var *var, struct termios term);
void	termcaps(t_var *var, struct termios *term, struct termios *term1);
void	word(t_list **history, t_var *var,  t_history **hist);
void	backsp(t_list **history, t_var *var,  t_history **hist);
void	down(t_list **history, t_var *var,  t_history **hist);
void	up(t_list **history, t_var *var,  t_history **hist);
int		ft_putchar (int c);
char	*write_lists(t_list *history, t_history *hist, t_var *var);
void	split_into_commands(char *term_str, t_var *var, struct termios term1);
char	**alloc_mem_for_word(char **com, int k, char *fin_str);
char	**spec_symbols(t_all *main_struct, char **com, char **buf, int k);
char	*find_variable_in_env(t_all *main_struct, char *varible, int fl_to_free);

t_history	*exact_list(t_list *history, t_var *var);
void	get_exact_str(t_list *history, t_history **list_struct, int numb);
void	prev_hist(t_list *history, t_var *var);

// Main builtins functions
int		ft_exit(t_all *main_struct, char **arr);
void	ft_echo(t_all *main_struct, char **arr);
void	ft_cd(t_all *main_struct, char **arr);
void	ft_pwd(t_all *main_struct, char **arr);
void	ft_export(t_all *main_struct, char **args);
void	ft_env(t_all *main_struct, char **arr);
void	ft_unset(t_all *main_struct, char **arr);

// Builtins utils
int		get_arr_len(char *arr[]);
char	**add_vars(t_all *main_struct, char **env, char *arg, char **vars);
char	*ft_strcat(char *s1, char *s2);
void	set_env(t_all *main_struct, t_env *s_env, char **env);
void	free_arr(char **arr);
int		ft_isnum(char *str);
void	print_with_quotes(char *str);
int		ft_strncmp_export(const char *s1, const char *s2, size_t n);
int		check_identifier(char *arg, int is_export);

// errors
void	error_msg(char *str, int is_errno, t_all *main_struct, int new_state);


char	**alloc_mem_for_word(char **com, int k, char *fin_str);
//work with env
char	*return_from_env(char *variable, char *final_str, int fl_to_free);
char	*find_variable_in_env(t_all *main_struct, char *varible, int fl_to_free);
void	join_status_or_envs_var(t_var *var, char *var_in_env, char **word, char **command);

// splitting by pipes
void	divide_big_list(t_list **inner_list, t_var *var, int words_q);
void	open_accord_redir(t_in_list *in_inner, t_var *var, int *j, int *index);

// skipping redirs
void	split_by_redirs(t_var *var, char *word, int *k);
int		check_if_redir(t_var *var, char *word, int *k);
void	input(t_var *var, char **into_array, int *k, int *i);
void	output_types(t_var *var, int *i, char **into_array, int *k);

// анализ спец символов
char	*deal_with_spec_smbls(t_list *com_in_str, t_var *var, char *word);
void	word_with_spec_symbols(char **final_str, char **term_str, char *ch);
int		find_exact_symb(char *symbols, char c);
int		symbols(char *sym, char *word);
int		dollar_in_quot(t_var *var, char **word,char **command);
void	dollar(char **word, t_var *var, char **command);
void	single_quotes(char **word, t_var *var, char **command);
void	quot_in_dquots(t_var *var, char **command, char **word);
void	building_word(char **str1, char *str2);
void	backslash(char **word, char **command, t_var *var);

int		check_if_pipe(char *final_str);
void	ft_split_pipes(t_var *var, char *final_str, char c, int *k);
int		check_if_redir(t_var *var, char *word, int *k);
void	split_by_redirs(t_var *var, char *word, int *k);

void	put_array_into_list(int q_words, int *i, t_var *var, t_in_list *inner_struct);
void	define_inpipelist(t_in_list **in_pipelist);


void	execute_part(t_list *com_in_str, t_var *var);
void	func(t_list *com_in_str, t_var	*var);
void	other_command(t_var *var, t_list *inner, char *token);
int		check_work_redirs(t_list *pipe_list, t_var *var);
void	redir_input(t_reds *reds);
void	redir_outputs(t_reds *reds, char *type);

void	handle_pipes(t_list *pipe_list, t_var *var);
char	*find_path(t_var *var);
char	*join_token_slash(char *token);
void	child_work(t_var *var, t_list *pipe_list, t_exec *exec_vars);
// void	child_work(t_var *var, t_list *pipe_list, char *to_token);
int	check_command(t_var *var, t_list *pipe_list, t_exec *exec_vars);

void	free_pipelist(t_list *com_in_str);
void	free_innerstruct(t_list *com_in_str);
void	free_vars(t_var *var);
void	cleaning(t_list *com_in_str);
#endif
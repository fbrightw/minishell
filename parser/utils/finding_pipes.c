#include "../../includes/minishell.h"

int	check_if_pipe(char *final_str)
{
	if (!find_exact_symb(final_str, '|'))
		return (0);
	else
		return (1);
}

void	split_by_pipes(t_list **pipe_list, t_in_list *in_pipelist, t_var *var)
{
	var->i = 0;
	while (var->words[var->i])
	{
		if (var->words[var->i] && !strcmp(var->words[var->i], "|"))
		{
			var->pipe_amount++;
			put_arr_in_list(var->k, &(var->i), var, in_pipelist);
			var->k = 0;
			ft_lstadd_back(pipe_list, ft_lstnew(in_pipelist));
			define_inpipelist(&in_pipelist);
			free(var->words[var->i]);
		}
		else
			var->k++;
		var->i++;
	}
	if (var->pipe_amount > 0 && var->k > 0)
	{
		put_arr_in_list(var->k, &(var->i), var, in_pipelist);
		ft_lstadd_back(pipe_list, ft_lstnew(in_pipelist));
	}
	else if (var->pipe_amount > 0 && var->k == 0)
		printf("syntax syntax error near unexpected token\n");
}

void	divide_big_list(t_list **pipe_list, t_var *var, int words_q)
{
	t_in_list	*in_pipelist;
	int			i;
	int			j;
	int			k;

	i = 0;
	k = 0;
	var->i = 0;
	var->k = 0;
	var->fl_error = 0;
	define_inpipelist(&in_pipelist);
	var->pipe_amount = 0;
	split_by_pipes(pipe_list, in_pipelist, var);
	if (!var->pipe_amount)
	{
		i = 0;
		k = 0;
		while (var->words[k])
			k++;
		i = k;
		put_arr_in_list(k, &i, var, in_pipelist);
		ft_lstadd_back(pipe_list, ft_lstnew(in_pipelist));
	}
}

void	before_pipe(t_var *var, char **final_str, int *k)
{
	char	*word;
	char	*get_to;

	word = NULL;
	while (**final_str && **final_str != '|')
	{
		var->temp[0] = **final_str;
		building_word(&word, var->temp);
		(*final_str)++;
	}
	if (word)
	{
		*k += 1;
		var->words = alloc_mem_for_word(var->words, *k, word);
		word = NULL;
	}
}

void	ft_split_pipes(t_var *var, char *final_str, char c, int *k)
{
	char	*temp;
	int		i;

	i = 0;
	var->temp[1] = '\0';
	while (*final_str)
	{
		before_pipe(var, &final_str, k);
		if (*final_str == '|')
		{
			temp = ft_strdup("|");
			*k += 1;
			var->words = alloc_mem_for_word(var->words, *k, temp);
			final_str++;
		}
	}
}

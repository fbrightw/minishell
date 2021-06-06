#include "../../includes/minishell.h"

int	check_if_pipe(char *final_str)
{
	if (!find_exact_symb(final_str, '|'))
		return (0);
	else
		return (1);
}

void	split_list_by_pipes(t_list **pipe_list, t_in_list *in_pipelist, t_var *var)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (var->words[i])
	{
		if (var->words[i] && !strcmp(var->words[i], "|"))
		{
			var->pipe_amount++;
			put_array_into_list(k, &i, var, in_pipelist);
			k = 0;
			ft_lstadd_back(pipe_list, ft_lstnew(in_pipelist));
			define_inpipelist(&in_pipelist);
			free(var->words[i]);
		}
		else
			k++;
		i++;
	}
	if (var->pipe_amount > 0 && k > 0)
	{
		put_array_into_list(k, &i, var, in_pipelist);
		ft_lstadd_back(pipe_list, ft_lstnew(in_pipelist));
	}
	else if (var->pipe_amount > 0 && k == 0)
		printf("ERROR\n"); // last word is PIPE
}

void	divide_big_list(t_list **pipe_list, t_var *var, int words_q)
{
	t_in_list *in_pipelist;
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	define_inpipelist(&in_pipelist);
	var->pipe_amount = 0;
	split_list_by_pipes(pipe_list, in_pipelist, var);
	if (!var->pipe_amount)
	{
		i = 0;
		k = 0;
		while (var->words[k])
			k++;
		i = k;
		put_array_into_list(k, &i, var, in_pipelist);
		ft_lstadd_back(pipe_list, ft_lstnew(in_pipelist));
	}
}

void	ft_split_pipes(t_var *var, char *final_str, char c, int *k)
{
	int i;
	char *word = NULL;

	i = 0;
	var->temp[1] = '\0';
	while (final_str[i])
	{
		while (final_str[i] && final_str[i] != '|')
		{
			var->temp[0] = final_str[i];
			building_word(&word, var->temp);
			i++;
		}
		if (word)
		{
			*k += 1;
			char *get_to = ft_strdup(word);
			var->words = alloc_mem_for_word(var->words, *k, get_to);
			free(word);
			word = NULL;
		}
		if (final_str[i] == '|')
		{
			char *temp = ft_strdup("|");
			*k += 1;
			var->words = alloc_mem_for_word(var->words, *k, temp);
		}
		i++;
	}
}

#include "../../includes/minishell.h"

int	check_if_pipe(char *final_str)
{
	if (!find_exact_symb(final_str, '|'))
		return (0);
	else
		return (1);
}

void	put_array_into_list(int q_words, int *i, t_var *var, t_in_list *inner_struct)
{
	int k;
	int j;
	int word_index;

	k = 0;
	j = 0;
	word_index = *i - q_words;
	while (j < q_words)
	{
		if (var->words[word_index])
		{
			if (!strcmp(var->words[word_index], ">") || !strcmp(var->words[word_index], ">>") ||
				!strcmp(var->words[word_index], "<"))
				open_accord_redir(inner_struct, var, &j, &word_index);
			else
			{
				k += 1;
				inner_struct->args = alloc_mem_for_word(inner_struct->args, k, var->words[word_index]);
				// printf("%s\n", var->words[word_index]);
				j++;
				word_index++;
			}
		}
	}
}

void	define_inpipelist(t_in_list **in_pipelist)
{
	*in_pipelist = malloc(sizeof(t_in_list));
	(*in_pipelist)->args = (char**)malloc(sizeof(char*));
	(*in_pipelist)->args[0] = NULL;
	(*in_pipelist)->reds_struct = NULL;
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
			i++;
		}
		else
		{
			i++;
			k++;
		}
	}
	if (var->pipe_amount > 0 && k > 0)
	{
		put_array_into_list(k, &i, var, in_pipelist);
		ft_lstadd_back(pipe_list, ft_lstnew(in_pipelist));
	}
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
	// i = 0;
	// while (((t_in_list*)((*pipe_list)->content))->args[i])
	// {
	// 	printf("%s\n", ((t_in_list*)((*pipe_list)->content))->args[i]);
	// 	i++;
	// }
	free(var->words);
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
			word = NULL;
		}
		if (final_str[i] == '|')
		{
			*k += 1;
			var->words = alloc_mem_for_word(var->words, *k, "|");
		}
		i++;
	}
	free(word);
}

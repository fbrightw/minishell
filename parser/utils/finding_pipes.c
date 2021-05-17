#include "../../includes/minishell.h"

int	check_if_pipe(char *final_str)
{
	if (!find_exact_symb(final_str, '|'))
		return (0);
	else
		return (1);
}

void	count_pipes(t_list *com_in_str, int *pipe_amount)
{
	char **array;
	int i;

	while (com_in_str)
	{
		i = 0;
		array =  ((t_into_lists *)(com_in_str->content))->args;
		while (array[i])
		{
			if (!strcmp(array[i], "|"))
				*pipe_amount += 1;
			i++;
		}
		com_in_str = com_in_str -> next;
	}
}

void	ft_split_pipes(t_into_lists *vars, char *final_str, char c, int *k)
{
	int i;
	char *word = NULL;
	char temp[2];

	i = 0;
	temp[1] = '\0';
	while (final_str[i])
	{
		while (final_str[i] && final_str[i] != '|')
		{
			temp[0] = final_str[i];
			building_word(&word, temp);
			i++;
		}
		if (word)
		{
			*k += 1;
			char *get_to = ft_strdup(word);
			vars->args = alloc_mem_for_word(vars->args, *k, get_to);
			word = NULL;
		}
		if (final_str[i] == '|')
		{
			*k += 1;
			vars->args = alloc_mem_for_word(vars->args, *k, "|");
		}
		i++;
	}
	free(word);
}

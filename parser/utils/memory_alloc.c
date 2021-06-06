#include "../../includes/minishell.h"

char	**alloc_mem_for_word(char **com, int k, char *fin_str)
{
	char	**new_com;
	int		i;

	i = 0;
	new_com = (char**)malloc(sizeof(char*) * (k + 1));
	while (com[i])
	{
		new_com[i] = com[i];
		i++;
	}
	new_com[i] = ft_strdup(fin_str);
	new_com[i + 1] = 0;
	free(fin_str);
	if (com)
		free(com);
	return (new_com);
}

void	put_array_into_list(int q_words, int *i, t_var *var, t_in_list *inner_struct)
{
	int k;
	int j;
	int word_index;

	k = 0;
	j = 0;
	var->fl_error = 0;
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
				j++;
				word_index++;
			}
		}
		else
			break;
	}
}

void	define_inpipelist(t_in_list **in_pipelist)
{
	*in_pipelist = malloc(sizeof(t_in_list));
	(*in_pipelist)->args = (char**)malloc(sizeof(char*));
	(*in_pipelist)->args[0] = NULL;
	(*in_pipelist)->reds_struct = NULL;
}

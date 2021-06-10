#include "../../includes/minishell.h"

char	**alloc_mem_for_word(char **com, int k, char *fin_str)
{
	char	**new_com;
	int		i;

	i = 0;
	new_com = (char **)malloc(sizeof(char *) * (k + 1));
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

void	no_redirs(t_in_list *in_struct, t_var *var, int *w_index)
{
	var->k += 1;
	in_struct->args = alloc_mem_for_word(in_struct->args, \
	var->k, var->words[*w_index]);
	var->j++;
	*w_index += 1;
}

void	put_arr_in_list(int q_words, int *i, t_var *var, t_in_list *in_struct)
{
	int	w_index;

	var->k = 0;
	var->j = 0;
	var->fl_error = 0;
	w_index = *i - q_words;
	while (var->j < q_words)
	{
		if (var->words[w_index])
		{
			if (!ft_strcmp(var->words[w_index], ">") \
				|| !ft_strcmp(var->words[w_index], ">>") \
					|| !ft_strcmp(var->words[w_index], "<"))
				open_accord_redir(in_struct, var, &(var->j), &w_index);
			else
				no_redirs(in_struct, var, &w_index);
		}
		else
			break ;
	}
}

void	define_inpipelist(t_in_list **in_pipelist)
{
	*in_pipelist = malloc(sizeof(t_in_list));
	(*in_pipelist)->args = (char **)malloc(sizeof(char *));
	(*in_pipelist)->args[0] = NULL;
	(*in_pipelist)->reds_struct = NULL;
}

void	alloc_mem_for_pipes(t_var *var, int fl)
{
	int	i;

	i = 0;
	if (!fl)
	{
		var->processes = (int *)malloc(sizeof(int) * var->procces_quant);
		var->pipes = (int **)malloc(sizeof(int *) * (var->procces_quant));
		while (i < var->procces_quant - 1)
		{
			var->pipes[i] = malloc(sizeof(int) * 2);
			i++;
		}
		var->pipes[i] = NULL;
	}
	else
		free_processes(var);
}

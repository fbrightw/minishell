#include "../../includes/minishell.h"

void	redir_outputs(t_reds *reds, char *type)
{
	dup2(reds->file_fd, 1);
	close(reds->file_fd);
}

void	redir_input(t_reds *reds)
{
	dup2(reds->file_fd, 0);
	close(reds->file_fd);
}

int	check_work_redirs(t_list *pipe_list, t_var *var)
{
	t_list	*reds_struct;
	t_reds	*reds;
	int		type;

	reds_struct = ((t_in_list *)(pipe_list->content))->reds_struct;
	while (pipe_list)
	{
		while (reds_struct)
		{
			reds = (t_reds *)(reds_struct->content);
			type = reds->type;
			if (type == 0)
				redir_input(reds);
			else if (type == 1)
				redir_outputs(reds, "OUTPUT");
			else if (type == 2)
				redir_outputs(reds, "APP_OUTPUT");
			else if (type == -1)
				return (0);
			reds_struct = reds_struct->next;
		}
		pipe_list = pipe_list->next;
	}
	return (1);
}

void	split_by_redirs(t_var *var, char *word, int *k)
{
	char	*into_array;
	int		i;

	i = 0;
	into_array = NULL;
	var->temp[1] = '\0';
	var->word = word;
	while (var->word[i])
	{
		if (var->word[i] == OUTPUT)
			output_types(var, &i, &into_array, k);
		else if (var->word[i] == INPUT)
			input(var, &into_array, k, &i);
		else
		{
			var->temp[0] = var->word[i];
			building_word(&into_array, var->temp);
			i++;
		}
	}
	if (into_array)
	{
		*k += 1;
		var->words = alloc_mem_for_word(var->words, *k, into_array);
	}
}

int	check_if_redir(t_var *var, char *word, int *k)
{
	while (*word)
	{
		if (*word == OUTPUT || *word == INPUT)
			return (1);
		word++;
	}
	return (0);
}

#include "../../includes/minishell.h"

void	input(t_var *var, char **into_array, int *k, int *i)
{
	// char red[1] = "<";
	// var->temp[1] = '\0';
	var->temp[0] = '<';

	if (*into_array)
	{
		*k += 1;
		var->words = alloc_mem_for_word(var->words, *k, *into_array);
		*into_array = NULL;
	}
	*k += 1;
	var->words = alloc_mem_for_word(var->words, *k, var->temp);
	*i += 1;
}

void	split_by_redirs(t_var *var, char *word, int *k)
{
	int i;
	char *into_array = NULL;

	i = 0;
	var->temp[1] = '\0';
	var->word = ft_strdup(word);
	while (var->word[i])
	{
		if (var->word[i] == OUTPUT) // ">"
			output_types(var, &i, &into_array, k);
		else if (var->word[i] == INPUT)
		{
			// write(1, "YA\n", 3);
			input(var, &into_array, k, &i);
		}
		else
		{
			var->temp[0] = word[i];
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

int		check_if_redir(t_var *var, char *word, int *k)
{
	while (*word)
	{
		if (*word == OUTPUT || *word == INPUT)
			return (1);
		word++;
	}
	return (0);
}

void	output_types(t_var *var, int *i, char **into_array, int *k)
{
	*i += 1;
	if (*into_array)
	{
		*k += 1;
		var->words = alloc_mem_for_word(var->words, *k, *into_array);
		*into_array = NULL;
	}
	if (var->word[*i] && var->word[*i] == OUTPUT) // ">>"
	{
		char red[3];
		red[0] = '>';
		red[1] = '>';
		red[2] = '\0';
		*into_array = ft_strdup(red);
		*k += 1;
		*i += 1;
		var->words = alloc_mem_for_word(var->words, *k, *into_array);
		*into_array = NULL;
	}
	else
	{
		char red[2] = ">";
		*into_array = ft_strdup(red);
		*k += 1;
		var->words = alloc_mem_for_word(var->words, *k, *into_array);
		*into_array = NULL;
	}
}
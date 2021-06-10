#include "../../includes/minishell.h"

void	input(t_var *var, char **into_array, int *k, int *i)
{
	char	*temp;

	var->temp[0] = '<';
	var->temp[1] = '\0';
	temp = ft_strdup(var->temp);
	if (*into_array)
	{
		*k += 1;
		var->words = alloc_mem_for_word(var->words, *k, *into_array);
		*into_array = NULL;
	}
	*k += 1;
	var->words = alloc_mem_for_word(var->words, *k, temp);
	*i += 1;
}

void	output(t_var *var, char **into_array, int *k, int *i)
{
	char	red[3];

	red[0] = '>';
	red[1] = '>';
	red[2] = '\0';
	*into_array = ft_strdup(red);
	*k += 1;
	*i += 1;
	var->words = alloc_mem_for_word(var->words, *k, *into_array);
	*into_array = NULL;
}

void	output_types(t_var *var, int *i, char **into_array, int *k)
{
	char	red[2];

	red[1] = '\0';
	*i += 1;
	if (*into_array)
	{
		*k += 1;
		var->words = alloc_mem_for_word(var->words, *k, *into_array);
		*into_array = NULL;
	}
	if (var->word[*i] && var->word[*i] == OUTPUT)
		output(var, into_array, k, i);
	else
	{
		red[0] = '>';
		*into_array = ft_strdup(red);
		*k += 1;
		var->words = alloc_mem_for_word(var->words, *k, *into_array);
		*into_array = NULL;
	}
}

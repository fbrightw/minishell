#include "../includes/minishell.h"

char	*find_variable_in_env(t_all *main_struct, char *varible, int fl_to_free)
{
	int i;
	char *final_str;

	i = 0;
	final_str = NULL;
	while (main_struct->env[i])
	{
		if (!ft_strncmp(varible, main_struct->env[i], ft_strlen(varible)) && main_struct->env[i][ft_strlen(varible)] == '=')
		{
			final_str = ft_substr(main_struct->env[i], ft_strlen(varible)+ 1, ft_strlen(main_struct->env[i]) - ft_strlen(varible) - 1);
			break;
		}
		else
			i++;
	}
	if (!final_str)
	{
		final_str = malloc(sizeof(char));
		final_str[0] = '\0';
	}
	if (fl_to_free)
		free(varible);
	return (final_str);
}

// char	*build_word(char **term_str, char symb_of_stop, char *temp)
// {
// 	char *final_str;

// 	final_str = NULL;
// 	while (**term_str != symb_of_stop && **term_str)
// 	{
// 		temp[0] = **term_str;
// 		if (!final_str)
// 			final_str = ft_strdup(temp);
// 		else
// 			final_str = ft_strjoin(final_str, temp);
// 		(*term_str)++;
// 	}
// 	// if (**buf != '\'')
// 	// 	write(1, "NEED DO SMTH\n", 20);
// 	return (final_str);
// }

// char	**spec_symbols(t_all *main_struct, char **com, char **term_str, int k)
// {
// 	int i;
// 	char *final_str;
// 	char temp[2];

// 	i = 0;
// 	temp[1] = '\0';
// 	final_str = NULL;
// 	if (**term_str == '\'')
// 	{
// 		(*term_str)++;
// 		final_str = build_word(term_str, '\'', temp);
// 		com = alloc_mem_for_word(com, k, final_str);
// 	}
// 	else if (**term_str == '$' || **term_str == '\"')
// 	{
// 		if (**term_str == '\"')
// 		{
// 			(*term_str)++;
// 			if (**term_str == '$')
// 			{
// 				final_str = build_word(term_str, '"', temp);
// 				// (*term_str)++;
// 				// final_str = build_word(term_str, '"', temp);
// 			}
// 			else
// 				final_str = build_word(term_str, '"', temp);
// 		}
// 		else
// 		{
// 			(*term_str)++;
// 			final_str = build_word(term_str, ' ', temp);
// 		}
// 		final_str = find_variable_in_env(main_struct, final_str, 1);
// 		com = alloc_mem_for_word(com, k, final_str);
// 	}
// 	else if (**term_str == '\\')
// 	{
// 		(*term_str)++;
// 		// if (!(ft_strchr("\'\"$<>?", **term_str)))
// 		final_str = build_word(term_str, ' ', temp);
// 		com = alloc_mem_for_word(com, k, final_str);
// 	}
// 	(*term_str)++;
// 	return (com);
// }
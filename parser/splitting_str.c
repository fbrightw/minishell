#include "../includes/minishell.h"

// buf = "ls -al | pwd ; echo "PATH" fg"
// needed result : ["ls" "-al" "|" "pwd" ] -> ["echo" "PATH"]

char	**alloc_mem_for_word(char **com, int k, char *fin_str)
{
	char	**new_com;
	int		i;
	int		l1;

	i = 0;
	new_com = (char**)malloc(sizeof(char*) * (k + 1));
	while (com[i])
	{
		new_com[i] = com[i];
		i++;
	}
	new_com[i] = fin_str;
	new_com[i + 1] = 0;
	if (com)
		free(com);
	return (new_com);
}

void	word_with_spec_symbols(char **final_str, char **term_str)
{
	char *temp;

	temp = malloc(sizeof(char*));
	temp[1] = '\0';
	while (**term_str != ' ' && **term_str)
	{
		temp[0] = **term_str;
		if (*final_str)
			*final_str = ft_strjoin(*final_str, temp);
		else
			*final_str = ft_strdup(temp);
		(*term_str)++;
	}
	free(temp);
}

void	filling_arr_in_list(t_list **com_in_str, char **term_str, char *temp, t_into_lists *vars)
{
	char *final_str;
	int k;
	int i;
	char *temp_str;

	k = 1;
	i = 0;
	final_str = NULL;
	vars->args = (char**)malloc(sizeof(char*));
	vars->args[0] = NULL;
	while (!ft_strchr(";", **term_str) && (**term_str))
	{
		if (**term_str == ' ')
		{
			vars->args = alloc_mem_for_word(vars->args, k, final_str); // новая память ( старое кол-во слов + новое слово)
			while (**term_str == ' ')
				(*term_str)++;
			k += 1;
			final_str = NULL;
		}
		else if (ft_strchr("\'\"$<>?", **term_str))
			word_with_spec_symbols(&final_str, term_str);
		else
		{
			temp[0] = **term_str;
			if (!final_str)
				final_str = ft_strdup(temp); //первый маллок final str здесь !
			else
				final_str = ft_strjoin(final_str, temp);
			(*term_str)++;
		}
	}
	if ((!**term_str || **term_str == ' ') && final_str)
	{
		k += 1;
		vars->args = alloc_mem_for_word(vars->args, k, final_str);
	}
	vars->args = vars->args;
	i = 0;
	// while (vars->before_changes[i])
	// {
	// 	printf("%s\n", vars->before_changes[i]);
	// 	i++;
	// }
	ft_lstadd_back(com_in_str, ft_lstnew(vars)); //течет
	free(final_str);
	temp = NULL;
}

void	find_coms_args(t_list **com_in_str, char **term_str, t_into_lists *vars)
{
	int arr_row;
	char *temp_for_one_ch;

	temp_for_one_ch = malloc(sizeof(char) * 2);
	temp_for_one_ch[1] = '\0';
	// двумерный массив состоящий из n строк, где n - количество слов до |, ;, <>
	filling_arr_in_list(com_in_str, term_str, temp_for_one_ch, vars);
	int i = 0;
	free(temp_for_one_ch);
}

void	split_into_commands(char *term_str, t_all *main_struct, t_var	*var)
{
	t_list *com_in_str;
	t_into_lists vars;

	int i;

	i = 0;
	com_in_str = NULL;
	printf("str = %s\n", term_str);
	while (*term_str)
	{
		if (!ft_strchr(";", *term_str)) // not |;<>
		{
			while (*term_str == ' ')
				term_str++;
			find_coms_args(&com_in_str, &term_str, &vars);
		}
		else
			term_str++;
	}
	// we need to check what it is in array and then send into built ins functions
	// wrote function that checks that it is built-in(skips spec symbols)

	// while (ft_lstsize(com_in_str))
	// {
		// com_in_str = com_in_str->next;
		// write(1, ((t_into_lists *)(com_in_str->content))->before_changes[0], 20);
		// printf("%s\n", ((t_into_lists *)(com_in_str->content))->before_changes[0]);
		is_it_com(&com_in_str, main_struct, var);
	// }


	// send to the rvinnie part (execute commands)
	// while (ft_lstsize_n(com_in_str))
	// {
	// 	// printf("%s\n", com_in_str->args[0]);
	// 	// разделить по пайпам;
	// 	// if (!isItBuiltin(main_struct, com_in_str->args)) //передаю массив, состоящий из команд + аргс (лист до ;)
	// 		// find_command()
	// 	is_it_builtin(main_struct, com_in_str->args);
	// 	com_in_str = com_in_str->next;
	// }
}

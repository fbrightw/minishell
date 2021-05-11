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

void	word_with_spec_symbols(char **final_str, char **term_str, char *ch)
{
	char temp[2];

	temp[1] = '\0';
	temp[0] = **term_str;
	building_word(final_str, temp);
	(*term_str)++;
	while (**term_str && **term_str != ch[0])
	{
		temp[0] = **term_str;
		building_word(final_str, temp);
		(*term_str)++;
	}
	temp[0] = **term_str;
	building_word(final_str, temp);
	(*term_str)++;
}

void	find_coms_args(t_list **com_in_str, char **term_str)
{
	char temp[2];
	char *final_str = NULL;
	int k;
	int i;
	t_into_lists *vars = malloc(sizeof(t_into_lists));

	k = 1;
	i = 0;
	vars->args = (char**)malloc(sizeof(char*));
	vars->args[0] = NULL;
	temp[1] = '\0';
	// двумерный массив состоящий из n строк, где n - количество слов до |, ;, <>
	while (**term_str && !ft_strchr(";", **term_str))
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
			word_with_spec_symbols(&final_str, term_str, ft_strchr("\'\"$<>?", **term_str));
		else
		{
			temp[0] = **term_str;
			building_word(&final_str, temp);
			(*term_str)++;
		}
	}
	if (final_str)
	{
		k += 1;
		vars->args = alloc_mem_for_word(vars->args, k, final_str);
	}
	ft_lstadd_back(com_in_str, ft_lstnew(vars)); //течет
}

int	is_it_b(char *token, t_var *var)
{
	int i;
	int j;
	int k;

	i = -1;
	j = 0;
	while (var->builtins[j])
	{
		k = 0;
		i = 0;
		while (token[i] && (token[i] == ft_toupper((var->builtins[j])[k]) || token[i] == ((var->builtins[j])[k])))
		{
			i++;
			k++;
		}
		if (!(token[i]) && !(var->builtins[j][k]))
			return (1);
		j++;
	}
	return (0);
}

void	func(t_list *com_in_str,  t_all *main_struct, t_var	*var)
{
	char *token;
	// printf("%d\n", ft_lstsize(com_in_str));
	while (com_in_str)
	{
		char **str = ((t_into_lists *)(com_in_str->content))->args;
		// printf("%s\n", str[0]);
		token = is_it_com(com_in_str, main_struct, var, str[0]);
		printf("%s\n", token);
		if (token)
		{
			if (is_it_b(token, var))
				printf("\nYES\n");
			else
				printf("NO\n");
		}
		com_in_str = com_in_str->next;
	}
}

void	split_into_commands(char *term_str, t_all *main_struct, t_var	*var)
{
	t_list *com_in_str;
	int i;

	i = 0;
	com_in_str = NULL;
	printf("str splitting = %s\n", term_str);
	while (*term_str)
	{
		printf("%s\n", term_str);
		if (!ft_strchr(";", *term_str)) // not |;<>
		{
			while (*term_str == ' ')
				term_str++;
			find_coms_args(&com_in_str, &term_str);
		}
		else
			term_str++;
	}
	// we need to check what it is in array and then send into built ins functions
	// wrote function that checks that it is built-in(skips spec symbols)
	func(com_in_str, main_struct, var);

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

#include "../includes/minishell.h"

// buf = "ls -al | pwd ; echo "PATH" fg"
// needed result : "ls -al"->|->"pwd"->";"->"echo" "PATH"
char	**alloc_mem_for_word(char **com, char *buf, int k, char *fin_str)
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

void	filling_arr_in_list(t_comm **com_in_str, char **buf, char *temp, t_all *main_struct)
{
	int arr_row;
	char *final_str;
	int k;
	int i;
	char **com;

	arr_row = 0;
	k = 1;
	i = 0;
	final_str = NULL;
	com = (char**)malloc(sizeof(char*));
	com[0] = NULL;
	while (!ft_strchr(";", **buf)) //    ls  m  s f
	{
		if (**buf == ' ')
		{
			com = alloc_mem_for_word(com, *buf, k, final_str); // новая память ( старое кол-во слов + новое слово)
			while (**buf == ' ')
				(*buf)++;
			arr_row += 1;
			k += 1;
			final_str = NULL;
		}
		else if (ft_strchr("\'\"$<>?", **buf))
			spec_symbols(com, buf);
		else
		{
			temp[0] = **buf;
			if (!final_str)
				final_str = ft_strdup(temp);
			else
				final_str = ft_strjoin(final_str, temp);
			(*buf)++;
		}
	}
	if (final_str)
	{
		com = alloc_mem_for_word(com, *buf, k, final_str);
		final_str = NULL;
	}
	ft_lstadd_back_n(com_in_str, ft_lstnew_n(com));
	while (com[i])
	{
		printf("%s\n", com[i]);
		i++;
	}
	// тут функции Леши
	temp = NULL;
}

void	find_coms_args(t_comm **com_in_str, char **buf, char *temp_for_one_ch, t_all *main_struct)
{
	int arr_row;

	temp_for_one_ch = malloc(sizeof(char) * 2);
	temp_for_one_ch[1] = '\0';
	// двумерный массив состоящий из n строк, где n - количество слов до |, ;, <>
	filling_arr_in_list(com_in_str, buf, temp_for_one_ch, main_struct);
}

void	split_into_commands(t_list **history, char **buf, t_all *main_struct)
{
	char *temp_for_one_ch;
	t_comm *com_in_str;
	int i;
	int fl;

	i = 0;
	fl = 0;
	com_in_str = NULL;
	temp_for_one_ch = NULL;
	while (**buf)
	{
		if (!ft_strchr(";", **buf)) // not |;<>
		{
			while (**buf == ' ')
				(*buf)++;
			find_coms_args(&com_in_str, buf, temp_for_one_ch, main_struct);
		}
		else
			(*buf)++;
	}
}

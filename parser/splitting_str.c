#include "../includes/minishell.h"

// buf = "ls -al | pwd ; echo "PATH" fg"
// needed result : "ls -al"->|->"pwd"->";"->"echo" "PATH"
void	alloc_mem_for_word(char **com, char *buf, int k, char *fin_str)
{
	char **new_com;
	int i;

	i = 0;
	new_com = (char**)malloc(sizeof(char*) * (k + 1));
	while (k > 0)
	{
		// write(1, "a", 1);
		if (com[i])
		{
			// write(1, "a", 1);
			new_com[i] = ft_strdup(com[i]);
		}
		else
		{
			// write(1, "a", 1);
			new_com[i] = malloc(sizeof(char));
			new_com[i] = NULL;
			// printf("%s\n", new_com[i]);
		}
		k--;
		i++;
	}
	// while (com[i])
	// {
	// 	free(com[i]);
	// 	i++;
	// }
	// if (com)
	// 	free(com);
	com = new_com;
	// printf("%s\n", com[0]);
}

void	filling_arr_in_list(t_comm **com_in_str, char **buf, char *temp)
{
	int arr_row;
	char *fin_str;
	int k;
	int i;
	char **com;
	char **new_com;

	arr_row = 0;
	k = 1;
	i = 0;
	fin_str = NULL;
	com = malloc(sizeof(char*));
	com[0] = malloc(sizeof(char));
	com[0] = NULL;
	while (!ft_strchr("|;<>", **buf)) //    ls  m;
	{
		if (**buf == ' ')
		{
			alloc_mem_for_word(com, *buf, k, fin_str); // новая память ( старое кол-во слов + новое слово)
			com[k - 1] = ft_strdup(fin_str);
			while (**buf == ' ')
				(*buf)++;
			arr_row += 1;
			k += 1;
			free(fin_str);
			fin_str = NULL;
		}
		else
		{
			temp[0] = **buf;
			if (!fin_str)
				fin_str = ft_strdup(temp);
			else
				fin_str = ft_strjoin(fin_str, temp);
			(*buf)++;
		}
	}
	ft_lstadd_back_n(com_in_str, ft_lstnew_n(com));
	while (com[i])
	{
		free(com[i]);
		i++;
	}
	free(com);
	free(temp);
	temp = NULL;
}

void	find_coms_args(t_comm **com_in_str, char **buf, char *temp_for_one_ch)
{
	int arr_row;

	temp_for_one_ch = malloc(sizeof(char) * 2);
	temp_for_one_ch[1] = '\0';
	// двумерный массив состоящий из n строк, где n - количество слов до |, ;, <>
	filling_arr_in_list(com_in_str, buf, temp_for_one_ch);
}

void	split_into_commands(t_list **history, char **buf)
{
	char *temp_for_one_ch;
	t_comm *com_in_str;
	int i;

	i = 0;
	com_in_str = NULL;
	temp_for_one_ch = NULL;
	while (**buf)
	{
		if (!ft_strchr("|;<>", **buf)) // not |;<>
		{
			while (**buf == ' ')
				(*buf)++;
			find_coms_args(&com_in_str, buf, temp_for_one_ch);
		}
		else
			(*buf)++;
	}
}

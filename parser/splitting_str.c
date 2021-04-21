#include "../includes/minishell.h"

// buf = "ls -al | pwd ; echo "PATH" fg"
// needed result : "ls -al"->|->"pwd"->";"->"echo" "PATH"
void	allocating_mem(t_comm *com_in_str, int k)
{
	int i;

	i = 0;
	// printf("%d\n", k);
	com_in_str->args = (char**)malloc(sizeof(char*) * k);
	while (k > 0)
	{
		com_in_str->args[i] = malloc(sizeof(char*));
		com_in_str->args[i] = NULL;
		k--;
		i++;
	}
}

void	find_coms_args(t_comm **com_in_str, int *i, char *buf)
{
	char *temp_for_one_ch;
	char *fin_str;
	int k;
	int i1;
	int arr_row;

	k = 1;
	i1 = *i;
	fin_str = NULL;
	temp_for_one_ch = malloc(sizeof(char) * 2);
	temp_for_one_ch[1] = '\0';
	// двумерный массив состоящий из n строк, где n - количество слов до |, ;, <>
	while (!ft_strchr("|;<>", buf[i1]))
	{
		if (buf[i1] == ' ')
			k++;
		i1++;
	}
	// printf("%d\n", k);
	// allocating_mem(*com_in_str, k);

	// не начинаются с пробела
	while (!ft_strchr("|;<>", buf[*i])) //    ls  m;
	{
		if (buf[*i] == ' ')
		{
			(*com_in_str)->args[arr_row] = ft_strdup(fin_str);
			arr_row += 1;
			free(fin_str);
			fin_str = NULL;
		}
		else
		{
			temp_for_one_ch[0] = buf[*i];
			if (!fin_str)
				fin_str = ft_strdup(temp_for_one_ch);
			else
				fin_str = ft_strjoin(fin_str, temp_for_one_ch);
		}
		*i += 1;
	}
	// printf("%s\n", (*com_in_str)->args[0]);
	ft_lstadd_back_n(com_in_str, ft_lstnew_n((*com_in_str)->args));
	*i += 1;
}

void	split_into_commands(t_list **history, char *buf)
{
	t_comm *com_in_str;
	int i;
	int k;
	int arr_row;
	int count_com;
	// cколько команд в строчке
	i = 0;
	k = 1;
	while (buf[i])
	{
		if (ft_strchr("|;<>", buf[i]))
			k++;
		i++;
	}

	com_in_str = NULL;
	// листы с двумерными массивами
	arr_row = 0;
	count_com = 0;
	i = 0;
	while (buf[i])
	{
		if (!ft_strchr("|;<>", buf[i])) // not |;<>
		{
			while (buf[i] == ' ')
				i++;
			find_coms_args(&com_in_str, &i, buf);
		}
		else
			i++;
	}
}
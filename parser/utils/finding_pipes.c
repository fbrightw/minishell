#include "../../includes/minishell.h"

void	indexes_of_pipe_red(t_into_lists *vars)
{
	int i;
	int q_pipes;
	int q_red;
	char *redir[3] = {">", "<", ">>"};

	i = 0;
	q_pipes = 0;
	q_pipes = 0;
	while (vars->args[i])
	{
		if (vars->args[i][0] == '|')
			q_pipes++;
		while (**redir)
		{
			if (symbols(*redir, vars->args[i]))
				q_red++;
			else
				(*redir)++;
		}
		i++;
	}
	if (q_red != 0)
	{
		vars->redirs = malloc(sizeof(int)* (q_red + 1));
		vars->redirs[q_red] = '\0';
	}
	if (q_pipes != 0)
	{
		vars->pipes = malloc(sizeof(int)* (q_pipes + 1));
		vars->pipes[q_pipes] = '\0';
	}

	i -= 1;
	q_pipes -= 1;
	q_red -= 1;
	// printf("%d %d\n", q_red, q_pipes);
	while (vars->args[i] && (q_pipes > 0 || q_red > 0))
	{
		if (vars->args[i][0] == '|')
		{
			vars->pipes[q_pipes] = i;
			q_pipes--;
		}
		while (**redir) // что-то из редир
		{
			if (symbols(*redir, vars->args[i]))
			{
				vars->redirs[q_red] = i;
				q_red--;
			}
			else
				(*redir)++;
		}
		i--;
	}
}

int	check_if_pipe(char *final_str)
{
	if (!find_exact_symb(final_str, '|'))
		return (0);
	else
		return (1);
}

void	count_pipes(t_list *com_in_str, int *pipe_amount)
{
	char **array;
	int i;

	while (com_in_str)
	{
		i = 0;
		array =  ((t_into_lists *)(com_in_str->content))->args;
		while (array[i])
		{
			if (!strcmp(array[i], "|"))
				*pipe_amount += 1;
			i++;
		}
		com_in_str = com_in_str -> next;
	}
}

void	ft_split_pipes(t_into_lists *vars, char *final_str, char c, int *k)
{
	int i;
	char *word = NULL;
	char temp[2];

	i = 0;
	temp[1] = '\0';
	while (final_str[i])
	{
		while (final_str[i] && final_str[i] != '|')
		{
			temp[0] = final_str[i];
			building_word(&word, temp);
			i++;
		}
		if (word)
		{
			*k += 1;
			char *get_to = ft_strdup(word);
			vars->args = alloc_mem_for_word(vars->args, *k, get_to);
			word = NULL;
		}
		if (final_str[i] == '|')
		{
			*k += 1;
			vars->args = alloc_mem_for_word(vars->args, *k, "|");
		}
		i++;
	}
	free(word);
}

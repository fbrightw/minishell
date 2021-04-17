#include "minishell.h"

int main(int argc, char const **argv, char const **envp)
{
	int row;
	int i;
	char **env_array;

	row = 0;
	i = 0;
	while (envp[row])
		row++;
	env_array = malloc(row * sizeof(char*));
	while (envp[i])
	{
		env_array[i] = ft_strdup(envp[i]);
		i++;
	}
	// i = 0;
	// while (env_array[i])
	// {
	// 	printf("%s\n", env_array[i]);
	// 	i++;
	// }
}
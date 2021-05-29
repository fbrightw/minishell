#include "../../includes/minishell.h"

void	print_with_quotes(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		write(1, &str[i], 1);
		i++;
	}
	if (!str[i])
		return ;
	write(1, &str[i++], 1);
	write(1,"\"",1);
	while (str[i])
		write(1, &str[i++],1);
	write(1,"\"",1);
}

int		ft_strncmp_export(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	while (s1[i] && (i < n))
	{
		if (s1[i] == s2[i])
			i++;
		else
		{
			if (s1[i] == '=' && s2[i] && s2[i] != '=')
				return (-1);
			if (s2[i] == '=' && s1[i] && s1[i] != '=')
				return (1);
			return (s1[i] - s2[i]);
		}
	}
	if (i < n)
		return (s1[i] - s2[i]);
	return (0);
}

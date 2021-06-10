#include "../../includes/minishell.h"

void	building_word(char **str1, char *str2)
{
	if (!*str1)
		*str1 = ft_strdup(str2);
	else
		*str1 = ft_strjoin(*str1, str2);
}

void	word_with_spec_symbols(char **final_str, char **term_str, char *ch)
{
	char	temp[2];

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
	if (**term_str)
	{
		temp[0] = **term_str;
		building_word(final_str, temp);
		(*term_str)++;
	}
}

int	find_exact_symb(char *symbols, char c)
{
	while (*symbols)
	{
		if (*symbols == c)
			return (1);
		symbols++;
	}
	return (0);
}

int	symbols(char *sym, char *word)
{
	while (*sym)
	{
		if (!ft_strchr(word, *sym))
			sym++;
		else
			return (1);
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (999);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return (s1[i] - s2[i]);
}

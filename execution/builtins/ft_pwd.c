#include "builtins.h"

void	ft_pwd(void)
{
	size_t	size;
	char	buf[122];
	char	*ptr;

	ptr = getcwd(buf, 122);				// don't forget error checker and errno and ptr == NULL
	ft_putstr_n(buf);
}
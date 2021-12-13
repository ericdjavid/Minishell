//HEADER_42

#include "libft.h"

size_t	ft_3dimlen(char ***mat)
{
	int	len;

	len = 0;
	while (mat[len])
		len++;
	return (len);
}

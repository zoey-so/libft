#include "libft.h"

char	*ft_strchr(const char *p, int ch)
{
	if (*p == (char)ch)
		return ((char *)p);
	while (*p++)
	{
		if (*p == (char)ch)
			return ((char *)p);
	}
	return (NULL);
}

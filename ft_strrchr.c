#include "libft.h"

char	*ft_strrchr(const char *p, int ch)
{
	char	*res;

	res = NULL;
	if (*p == (char)ch)
		res = (char *)p;
	while (*p++)
	{
		if (*p == (char)ch)
			res = (char *)p;
	}
	return (res);
}

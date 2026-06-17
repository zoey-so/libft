#include "libft.h"

char	*ft_strrchr(const char *p, int ch)
{
	char	*res;

	if (*p == (char)ch)
		res = (char *)p;
	while (*p++)
	{
		if (*p == (char)ch)
			res = (char *)p;
		p++;
	}
	return (res);
}
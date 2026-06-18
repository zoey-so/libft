#include "libft.h"

char	*ft_strrchr(const char *p, int ch)
{
	while (*p)
	{
		if (*p == (char)ch)
			return ((char *)p);
		p++;
	}
	if (ch == '\0')
		return ((char *)p);
	return (NULL);
}
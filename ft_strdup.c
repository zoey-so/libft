#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(str);
	if (!(dup = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_memcpy(dup, str, len + 1);
	return (dup);
}
#include "libft.h"

char	*ft_itoa(int n)
{
	char		*res;
	long int	nb;
	size_t		len;

	len = 0;
	nb = (((long int)n >> 31) ^ ((long int)n)) - ((long int)n >> 31);
	while (++len && nb > 9)
		nb /= 10;
	if (n < 0)
		len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = '\0';
	nb = (((long int)n >> 31) ^ ((long int)n)) - ((long int)n >> 31);
	while (len-- > 0)
	{
		res[len] = '0' + (nb % 10);
		nb /= 10;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}

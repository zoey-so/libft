/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 17:49:46 by smilch            #+#    #+#             */
/*   Updated: 2026/06/15 17:49:47 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t slen)
{
	size_t	n_len;

	if (!*to_find)
		return ((char *)str);
	n_len = ft_strlen(to_find);
	while (slen >= n_len)
	{
		if (ft_strncmp(str, to_find, n_len) == 0)
			return ((char *)str);
		str++;
		slen--;
	}
	return (NULL);
}
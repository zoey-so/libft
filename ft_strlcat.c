/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 17:48:41 by smilch            #+#    #+#             */
/*   Updated: 2026/06/15 17:48:42 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dsize)
{
	size_t	r_len;
	char	*dest_cp;

	dest_cp = dest;
	while (*dest && dsize)
	{
		dest++;
		dsize--;
	}
	r_len = dest - dest_cp;
	if (!dsize)
		return (r_len + ft_strlen(src));
	while (*src)
	{
		if (dsize - 1)
		{
			*(dest++) = *src;
			dsize--;
		}
		src++;
		r_len++;
	}
	*dest = '\0';
	return (r_len);
}

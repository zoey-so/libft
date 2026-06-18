/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 17:48:49 by smilch            #+#    #+#             */
/*   Updated: 2026/06/15 17:48:50 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	const char	*src_cp;
	size_t		left_size;

	src_cp = src;
	left_size = size;
	if (left_size)
	{
		while (--left_size)
		{
			if (*src == '\0')
			{
				*dest++ = *src++;
				break ;
			}
			*(dest++) = *(src++);
		}
	}
	if (!left_size)
	{
		if (size)
			*dest = '\0';
		while (*src++)
			;
	}
	return (src - src_cp - 1);
}

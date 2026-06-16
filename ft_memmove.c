/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 17:48:11 by smilch            #+#    #+#             */
/*   Updated: 2026/06/15 17:48:13 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	const char	*src;
	char		*dst;

	src = s2;
	dst = s1;
	if (src < dst)
	{
		src += n - 1;
		dst += n - 1;
		while (n-- > 0)
			*dst-- = *src--;
	}
	else
	{
		while (n-- > 0)
			*dst++ = *src++;
	}
	return (s1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 17:47:52 by smilch            #+#    #+#             */
/*   Updated: 2026/06/15 17:47:53 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*s1_cp;
	const char	*s2_cp;

	s1_cp = s1;
	s2_cp = s2;
	while (n)
	{
		if (*s1_cp++ != *s2_cp++)
			return (*--s1_cp - *--s2_cp);
		n--;
	}
	return (0);
}

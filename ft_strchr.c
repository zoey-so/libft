/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 17:48:31 by smilch            #+#    #+#             */
/*   Updated: 2026/06/15 17:48:33 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strchr(const char *str, int ch)
{
	if (*str == (char)ch)
		return ((char *)str);
	while (str++)
	{
		if (*str == (char)ch)
			return ((char *)str);
	}
	return ((char *) NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 16:58:49 by edvicair          #+#    #+#             */
/*   Updated: 2022/11/12 15:23:50 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	lensrc;
	size_t	lendest;

	i = 0;
	lensrc = ft_strlen(src);
	lendest = ft_strlen(dest);
	if (size <= lendest)
		lensrc += size;
	else
		lensrc += lendest;
	if (size > lendest)
	{
		while (src[i] && (lendest + 1) < size)
		{
			dest[lendest] = src[i];
			i++;
			lendest++;
		}
	}
	dest[lendest] = '\0';
	return (lensrc);
}

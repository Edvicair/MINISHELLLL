/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:35:32 by edvicair          #+#    #+#             */
/*   Updated: 2022/11/12 16:37:05 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*cpy_src;
	unsigned char	*cpy_dest;
	size_t			i;

	i = 0;
	cpy_src = (unsigned char *)src;
	cpy_dest = (unsigned char *)dest;
	while (i < n)
	{
		cpy_dest[i] = cpy_src[i];
		if (cpy_dest[i] == (unsigned char)c)
			return (&dest[i + 1]);
		i++;
	}
	return (NULL);
}

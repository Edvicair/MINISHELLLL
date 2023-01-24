/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:09:39 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/20 11:39:18 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*buya;
	size_t	i;

	i = 0;
	buya = (char *)malloc(sizeof(char) * len + 1);
	if (!buya)
		return (NULL);
	if (len == 0 || start >= ft_strlen(s))
	{
		buya[0] = '\0';
		return (buya);
	}
	while (i < len)
	{
		buya[i] = s[start];
		i++;
		start++;
	}
	buya[i] = '\0';
	return (buya);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:09:39 by edvicair          #+#    #+#             */
/*   Updated: 2022/12/08 11:49:45 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || (s1[i] == '\0' && s2[i] == '\0'))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i] || (s1[i] == '\0' && s2[i] == '\0'))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(t_msh *msh, const char *s)
{
	int		i;
	int		s_len;
	char	*s_cpy;

	i = 0;
	s_len = ft_strlen(s);
	s_cpy = (char *)malloc(sizeof(char) * s_len + 1);
	if (!s_cpy)
		return (NULL);
	while (s[i])
	{
		s_cpy[i] = s[i];
		i++;
	}
	s_cpy[i] = '\0';
	return (s_cpy);
}

char	*ft_strjoin(t_msh *msh, char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*dest;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1);
	len += ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	while (i < len)
	{
		while (s1[j])
			dest[i++] = s1[j++];
		j = 0;
		while (s2[j])
			dest[i++] = s2[j++];
	}
	dest[i] = '\0';
	return (dest);
}

bool	ft_strshr(const char *s, int c)
{
	size_t	i;
	char	*s_cpy;

	i = 0;
	s_cpy = (char *)s;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (1);
		i++;
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:16:56 by edvicair          #+#    #+#             */
/*   Updated: 2022/11/16 10:06:10 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_countword(const char *s)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	if (s[i] == '\0')
		return (n);
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	while (s[i])
	{
		if (((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
			&& (s[i - 1] >= 33 && s[i - 1] <= 126))
		{
			n++;
		}
		i++;
	}
	if (s[i - 1] >= 33 && s[i - 1] <= 126)
		n++;
	return (n);
}

static char	*ft_substrr(const char *s, int min, int max)
{
	int		i;
	char	*s2;

	s2 = malloc(sizeof(char *) * (max - min + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (min < max)
	{
		s2[i] = s[min];
		i++;
		min++;
	}
	s2[i] = '\0';
	return (s2);
}

static void	ft_free_idk(int n, char **s)
{
	while (n >= 0)
	{
		free(s[n]);
		n--;
	}
	free(s);
}

static	void	boucle(const char *s, char **s2)
{
	int	i;
	int	n;
	int	min;

	i = 0;
	n = 0;
	min = 0;
	while (s[i] != '\0')
	{
		while (s[i] && ((s[i] >= 9 && s[i] <= 13) || s[i] == 32))
			i++;
		min = i;
		while (s[i] && ((s[i] <= 9 && s[i] >= 13) || s[i] != 32 && s[i] != 10))
			i++;
		if (n < ft_countword(s))
		{
			s2[n] = ft_substrr(s, min, i);
			if (s2[n] == NULL)
				ft_free_idk(n, s2);
			n++;
		}
		s2[n] = NULL;
	}
}

char	**ft_split_space(char const *s)
{
	char	**s2;

	if (!s)
		return (NULL);
	s2 = malloc(sizeof(char *) * (ft_countword(s) + 1));
	if (s2 == NULL)
	{
		free(s2);
		return (0);
	}
	s2[ft_countword(s)] = 0;
	boucle(s, s2);
	return (s2);
}

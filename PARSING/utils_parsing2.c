/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:52:58 by motaouss          #+#    #+#             */
/*   Updated: 2023/01/11 16:15:19 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_pipe(char *str)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = 0;
	while (str[i])
	{
		if (str[i] == '|')
			pipe++;
		if (str[i] == '\'' || str[i] == '"')
			i = split_what(str, i, str[i]);
		i++;
	}
	return (pipe);
}

int	find_pipe(char *str, int i)
{
	while (str[i] != '|' && str[i])
	{
		i++;
	}
	if (str[i] = '\0')
		return (ft_strlen(str));
	return (i);
}

char	*ft_substr2(const char *s, int min, int max)
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

int		ft_strlen_redir(char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while(str[i])
	{
		k = i;
		if(str[i] == '\'' || str[i] == '"')
		{
			i = split_what(str, i, str[i]);
			j = j + (i - k);
		}
		if (str[i] == '<' || str[i] == '>')
			i = split_what(str, i, str[i]);
		if (str[i])
			i++;
		j++;
	}
	return (j);
}

char	*ft_substr_redir(char *s)
{
	int		i;
	int		j;
	char	quote;
	char	*s2;

	s2 = malloc(sizeof(char *) * (ft_strlen_redir(s) + 1));
	if (!s2)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			quote = s[i];
			s2[j] = s[i];
			i++;
			j++;
			while (s[i] != quote)
			{
				s2[j] = s[i];
				i++;
				j++;
			}
		}
		if (s[i] == '>' || s[i] == '<')
			i = split_what(s, i, s[i]);
		if (s[i] && s[i] != '>' && s[i] != '<')
		{
			s2[j] = s[i];
			i++;
			j++;
		}
	}
	s2[j] = '\0';
	return (s2);
}
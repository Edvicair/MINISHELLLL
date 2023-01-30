/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 20:16:33 by motaouss          #+#    #+#             */
/*   Updated: 2023/01/30 10:21:26 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	split_what(char *str, int i, char quote)
{
	if (quote == '\'' || quote == '"')
	{
		i++;
		while (str[i] != quote && str[i])
			i++;
		return (i);
	}
	else
	{
		i++;
		while (str[i] && (str[i] == ' ' || str[i] == '>' || str[i] == '<'))
			i++;
		while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<')
			i++;
		while (str[i] && str[i] == ' ')
			i++;
		return (i);
	}
}

int	strlen_quote(char *str, int min, int max)
{
	int		i;
	char	quote;

	i = min;
	while (str[i] != '\'' && str[i] != '"' && i < max)
		i++;
	if (i == max)
		return ((max - min) + 1);
	else
		quote = str[i];
	i = min;
	while (i < max)
	{
		if (str[i] == quote)
			min++;
		i++;
	}
	return ((max - min) + 1);
}

int	find_quote(char *str, int min, int max)
{
	while (min < max)
	{
		if (str[min] == '\'' || str[min] == '"')
			return (str[min]);
		min++;
	}
	return (0);
}

char	*ft_substr_pipe(const char *s, unsigned int start, unsigned int end)
{
	char	*buya;
	size_t	i;

	i = 0;
	buya = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!buya)
		return (NULL);
	if ((end - start) <= 0)
	{
		buya[0] = '\0';
		return (buya);
	}
	while (start < end)
	{
		buya[i] = s[start];
		i++;
		start++;
	}
	buya[i] = '\0';
	return (buya);
}

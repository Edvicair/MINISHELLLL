/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motaouss <motaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 04:21:36 by motaouss          #+#    #+#             */
/*   Updated: 2022/12/26 17:21:50 by motaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*space_chips(char *line)
{
	char	*str;
	int	i;

	i = 0;
	str = NULL;
	if (!(str))
		return (line);
	str = (char *)malloc(sizeof(char) * ft_strlen(line));
	while (line[i])
	{
		if	((line[i] >= 9 && line[i] <= 13) && line[i])
			str[i] = ' ';
		else
			str[i] = line[i];
		i++;
	}
	str[i] = '\0';
	free(line);
	return (str);
}


int	pipe_error(char *line)
{
	int	i;

	i = 0;
	while (((line[i] >= 9 && line[i] <= 13) || line[i] == ' ') && line[i])
		i++;
	if (line[i] == '|')
		return (1);
	while (line[i])
	{
		if (line[i] == '|')
		{
			i++;
			while (((line[i] >= 9 && line[i] <= 13) || line[i] == ' ') && line[i])
				i++;
			if (line[i] == '|' || line[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	redir_error(char *line)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			i = split_what(line, i, line[i]);
		if (line[i] == '>' || line[i] == '<')
		{
			j = i;
			if ((line[i] == '>' && line[i + 1] == '<') || (line[i] == '<' && line[i + 1] == '>') ||
			(line[i + 1] == '>' && line[i + 2] == '>') || (line[i + 1] == '<' && line[i + 2] == '<'))
				return (1);
			while (line[i + 1] == ' ')
				i++;
			if (!line[i + 1] || ((line[i + 1] == '>' || line[i + 1] == '<') && i != j) || line[i + 1] == '|')
				return (1);
		}
		if (!line[i]|| ((line[i] == '<' || line[i] == '>') && !line[i + 1]))
			return (1);
		i++;
	}
	return (0);
}

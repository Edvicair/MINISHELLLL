/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 04:21:36 by motaouss          #+#    #+#             */
/*   Updated: 2023/01/29 01:03:26 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*space_chips(char *line)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	str = (char *)malloc(sizeof(char) * ft_strlen(line) + 1);
	if (!(str))
		return (line);
	while (line[i])
	{
		if ((line[i] >= 9 && line[i] <= 13) && line[i])
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
			while (((line[i] >= 9 && line[i] <= 13) || line[i] == ' ')
				&& line[i])
				i++;
			if (line[i] == '|' || line[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

bool	redir_error_bis(char *line, int i)
{
	if ((line[i] == '>' && line[i + 1] == '<') || (line[i] == '<'
			&& line[i + 1] == '>') || (line[i + 1] == '>'
			&& line[i + 2] == '>') || (line[i + 1] == '<'
			&& line[i + 2] == '<'))
		return (1);
	return (0);
}

int	redir_error(char *line)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '"')
			i = split_what(line, i, line[i]);
		if (line[i] == '>' || line[i] == '<')
		{
			j = i;
			if (redir_error_bis(line, i))
				return (1);
			while (line[i + 1] == ' ')
				i++;
			if (!line[i + 1] || ((line[i + 1] == '>' || line[i + 1] == '<')
					&& i != j) || line[i + 1] == '|')
				return (1);
		}
		if (!line[i] || ((line[i] == '<' || line[i] == '>') && !line[i + 1]))
			return (1);
	}
	return (0);
}

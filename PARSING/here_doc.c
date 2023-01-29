/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:00:08 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/29 00:46:40 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*open_hdoc(char *word)
{
	char	*s;
	char	*tmp;

	s = ft_strjoin(".", word);
	while (access(s, F_OK) != -1)
	{
		tmp = s;
		s = ft_strjoin(".", tmp);
		free(tmp);
	}
	return (s);
}

char	*here_doc(char *word)
{
	int		hdoc;
	char	*line;
	char	*s;

	line = NULL;
	s = open_hdoc(word);
	hdoc = open(s, O_CREAT | O_WRONLY, 0644);
	if (hdoc < 0)
		return (NULL);
	while (1)
	{
		line = readline("=>");
		if (!ft_strncmp(line, word, ft_strlen(word)))
		{
			free(line);
			break ;
		}
		if (line)
			write(hdoc, line, ft_strlen(line));
		write(hdoc, "\n", 1);
		free(line);
	}
	close(hdoc);
	return (s);
}

void	unlink_here_doc(t_msh *msh, t_token *token)
{
	t_token	*cpy;

	cpy = token;
	while (cpy->redir)
	{
		if (cpy->redir->type == H_DOC)
		{
			close(msh->in);
			unlink(cpy->redir->feldup);
		}
		if (cpy->redir->next)
			cpy->redir = cpy->redir->next;
		else
			break ;
	}
}

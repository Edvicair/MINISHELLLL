/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tok.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:34:23 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/04 13:30:11 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_sep(char *s)
{
	int		i;
	int		count;
	bool	r;

	i = 0;
	count = 0;
	r = 0;
	while (s[i])
	{
		while (s[i] && ((s[i] == '<' || s[i] == '>') || r != 2))
		{
			if (s[i] == 32)
				r++;
			i++;
		}
		count++;
		i++;
	}
	count++;
	return (count);
}

char	*cut_redir(char *cmd)
{
	char	*cpy;
	int		i;
	int		j;
	int		r;

	i = 0;
	r = 0;
	j = 0;
	cpy = (char *)malloc(sizeof(char) * count_sep(cmd));
	if (!cpy)
		return (NULL);
	while (cmd[i])
	{
		if (cmd[i] == '<' || cmd[i] == '>')
			while (cmd[i] && ((cmd[i] == '<' || cmd[i] == '>') || r != 2))
			{
				if (cmd[i] == 32)
					r++;
				i++;
			}
		cpy[j++] = cmd[i++];
	}
	//free(cmd);
	cpy[j] = '\0';
	return (cpy);
}

t_token	*ft_token_new(t_msh *msh, char *cmd)
{
	t_token	*lst_token;
	char	*cpy;

	lst_token = (t_token *)malloc(sizeof(t_token));
	if (!lst_token)
		return (NULL);
	cpy = cut_redir(cmd);
	lst_token->cmd = tokenizator(cpy, msh);
	if (ft_strncmp(cmd, cpy, ft_strlen(cmd)))
		lst_token->redir = redi_less(cmd);
	else
		lst_token->redir = NULL;
	lst_token->next = 0;
	return (lst_token);
}

t_token	*ft_token_last(t_token *token)
{
	if (token)
	{
		while (token->next)
			token = token->next;
	}
	return (token);
}

void	ft_token_add_back(t_token **token, t_token *new)
{
	t_token	*lst_token;

	if (token)
	{
		if (*token)
		{
			lst_token = ft_token_last(*token);
			lst_token->next = new;
		}
		else
			*token = new;
	}
}

t_token	*ft_fill_token(t_msh *msh)
{
	char	**pipe;
	t_token	*token;
	int		i;

	i = 0;
	token = NULL;
	msh->pip = ft_strshr(msh->line, '|');
	pipe = ft_split(msh->line, '|');
	if (!pipe[i])
		return (token);
	while (pipe[i])
	{
		ft_token_add_back(&token, ft_token_new(msh, pipe[i]));
		i++;
	}
	ft_free_double(pipe);
	return (token);
}
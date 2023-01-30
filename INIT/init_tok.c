/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tok.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:34:23 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/30 12:28:04 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_token_new(t_msh *msh, char *cmd_p)
{
	t_token	*lst_token;
	char	*tmp;

	lst_token = (t_token *)malloc(sizeof(t_token));
	if (!lst_token)
		return (NULL);
	lst_token->redir = redi_less(cmd_p);
	tmp = ft_substr_redir(cmd_p);
	lst_token->cmd = tokenizator(tmp, ' ');
	int i = 0;
	while (lst_token->cmd[i])
	{
		printf("TOTO = %s\n", lst_token->cmd[i]);
		i++;
	}
	free(tmp);
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
	char		**pipe;
	t_token		*token;
	int			i;

	i = 0;
	token = NULL;
	pipe = tokenizator(msh->line, '|');
	if (!pipe[i])
		return (token);
	while (pipe[i])
	{
		ft_token_add_back(&token, ft_token_new(msh, pipe[i]));
		i++;
	}
	msh->pip = i - 1;
	ft_free_double(pipe);
	return (token);
}

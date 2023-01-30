/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:00:59 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/30 11:35:22 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	redir_in(t_redir *redir, t_msh *msh)
{
	if ((redir->type == RE_G || redir->type == H_DOC) && redir->feldup)
	{
		if (msh->in != 0)
			close(msh->in);
		msh->in = open(redir->feldup, O_RDONLY);
		if (msh->in < 0)
		{
			printf("\033[0;31m%s: No such file or directory\n", redir->feldup);
			return (1);
		}
	}
	return (0);
}

bool	redir_out(t_redir *redir, t_msh *msh)
{
	if (redir->type == RE_D && redir->feldup)
	{
		if (msh->out != 1)
			close(msh->out);
		msh->out = open(redir->feldup, O_CREAT | O_TRUNC | O_WRONLY, 0664);
		if (msh->out < 0)
		{
			printf("\033[0;31mcan't open %s\n", redir->feldup);
			return (1);
		}
	}
	else if (redir->type == RE_DD && redir->feldup)
	{
		if (msh->out != 1)
			close(msh->out);
		msh->out = open(redir->feldup, O_CREAT | O_APPEND | O_WRONLY, 0664);
		if (msh->out < 0)
		{
			printf("\033[0;31mcan't open %s\n", redir->feldup);
			return (1);
		}
	}
	return (0);
}

int	ft_check_redirection(t_msh *msh, t_token *token)
{
	t_redir	*cpy;
	bool	i;

	i = 0;
	cpy = token->redir;
	while (cpy && !i)
	{
		i += redir_in(cpy, msh);
		i += redir_out(cpy, msh);
		if (cpy->next)
			cpy = cpy->next;
		else
			break ;
	}
	return (i);
}

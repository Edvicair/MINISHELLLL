/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:00:59 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/20 01:59:46 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_in(t_redir *redir, t_msh *msh)
{
	if (redir->type == RE_G && redir->feldup)
	{
		if (msh->in != 0)
			close(msh->in);
		msh->in = open(redir->feldup, O_RDONLY);
		if (msh->in < 0)
			printf("can't open %s\n", redir->feldup);
	}
	else if (redir->type == H_DOC && redir->feldup)
	{
		if (msh->in != 0)
			close(msh->in);
		msh->in = msh->fd[1];
		if (msh->in < 0)
			printf("can't open %s\n", redir->feldup);
	}
}

void	redir_out(t_redir *redir, t_msh *msh)
{
	if (redir->type == RE_D && redir->feldup)
	{
		if (msh->out != 1)
			close(msh->out);
		msh->out = open(redir->feldup, O_CREAT | O_TRUNC | O_WRONLY, 0664);
		if (msh->out < 0)
			printf("can't open %s\n", redir->feldup);
	}
	else if (redir->type == RE_DD && redir->feldup)
	{
		if (msh->out != 1)
			close(msh->out);
		msh->out = open(redir->feldup, O_CREAT | O_APPEND | O_WRONLY, 0664);
		if (msh->out < 0)
				printf("can't open %s\n", redir->feldup);
	}
}

void	ft_check_redirection(t_msh *msh)
{
	t_redir *cpy;

	cpy = msh->token->redir;
	while (cpy)
	{
			redir_in(cpy, msh);
			redir_out(cpy, msh);
		if (cpy->next)
			cpy = cpy->next;
		else
			break;
	}
}

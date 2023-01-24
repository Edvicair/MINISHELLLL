/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motaouss <motaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:31:52 by motaouss          #+#    #+#             */
/*   Updated: 2023/01/20 04:19:36 by motaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	token_error(char *line)
{
	if ((pipe_error(line)))
		return (1);
	if ((is_quote(line)))
		return (1);
	if (redir_error(line))
		return (1);
	return (0);
}

int	parser(t_msh *msh)
{
	msh->line = space_chips(msh->line);
	if ((token_error(msh->line)))
	{
		printf("\x1b[31mSyntax Error\n");
		add_history(msh->line);
		return (0);
	}
	else if (msh->line[0] == '\0')
		return (0);
	else
	{
		add_history(msh->line);
		msh->line = add_expand(msh);
		if (msh->line[0] != '\0')
			msh->token = ft_fill_token(msh);
		return (1);
	}
}

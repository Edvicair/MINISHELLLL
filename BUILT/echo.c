/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:48:51 by edvicair          #+#    #+#             */
/*   Updated: 2022/12/01 14:03:46 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_option(t_msh *msh)
{
	size_t	i;

	if (msh->token->cmd[1] && msh->token->cmd[1][0] == '-')
	{
		i = 1;
		while (msh->token->cmd[1] && msh->token->cmd[1][i] == 'n')
		{
			i++;
			if (!msh->token->cmd[1][i])
				return (1);
		}
	}
	return (0);
}

void 	ft_echo_pipe(t_msh *msh, int i, int j, bool res)
{
	int *fdd;
	char *cmdd;
	
	fdd = msh->token->fd;
	while (msh->token->cmd[i])
	{
		cmdd = msh->token->cmd[i];
		if (i > j)
			printf(" ");
		write(fdd[1], &cmdd, ft_strlen(cmdd));
		i++;
	}
	if (res == 0)
		write(fdd[1], "\n", 1);
}

void	ft_echo(t_msh *msh)
{
	int	i;
	int	j;
	bool	res;

	res = check_option(msh);
	if (res == 1)
		i = 2;
	else
		i = 1;
	j = i;
	if (msh->pip)
	{
		ft_echo_pipe(msh, i, j, res);
		return ;
	}
	while (msh->token->cmd[i])
	{
		if (i > j)
			printf(" ");
		printf("%s", msh->token->cmd[i]);
		i++;
	}
	if (res == 0)
		printf("\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:48:51 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/20 08:39:08 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_option(char **cmd)
{
	size_t	i;

	if (cmd[1] && cmd[1][0] == '-')
	{
		i = 1;
		while (cmd[1] && cmd[1][i] == 'n')
		{
			i++;
			if (!cmd[1][i])
				return (1);
		}
	}
	return (0);
}

void 	ft_echo_pipe(t_msh *msh, char **cmd, int i, int j, bool res)
{
	char *cmdd;
	
	while (cmd[i])
	{
		cmdd = cmd[i];
		if (i > j)
			printf(" ");
		write(msh->fd[1], &cmdd, ft_strlen(cmdd));
		i++;
	}
	if (res == 0)
		write(msh->fd[1], "\n", 1);
}

void	ft_echo(t_msh *msh, char **cmd)
{
	int	i;
	int	j;
	int fd;
	bool	res;

	fd = 1;
	if (msh->out)
		fd = msh->out;
	res = check_option(cmd);
	if (res == 1)
		i = 2;
	else
		i = 1;
	j = i;
	if (msh->pip)
	{
		ft_echo_pipe(msh, cmd, i, j, res);
		return ;
	}
	while (cmd[i])
	{
		if (i > j)
			write(fd, " ", 1);
		write(fd, cmd[i], ft_strlen(cmd[i]));
		i++;
	}
	if (res == 0)
		write(fd, "\n", 1);
}

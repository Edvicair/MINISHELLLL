/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:48:51 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/24 06:28:55 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_option(char **cmd)
{
	size_t	i;

	if (cmd[1] && cmd[1][0] == '-')
	{
		i = 1;
		while (cmd[1] && cmd[1][i] == 'n')
		{
			i++;
			if (!cmd[1][i])
				return (2);
		}
	}
	return (1);
}

void	ft_echo_pipe(t_msh *msh, char **cmd, int i, int j)
{
	while (cmd[i])
	{
		if (i > j)
			write(msh->fd[1], cmd[i], ft_strlen(cmd[i]));
		write(msh->fd[1], cmd[i], ft_strlen(cmd[i]));
		i++;
	}
	if (check_option(cmd) == 1)
		write(msh->fd[1], "\n", 1);
}

void	ft_echo(t_msh *msh, char **cmd)
{
	int		i;
	int		j;
	int		fd;

	fd = 1;
	if (msh->out)
		fd = msh->out;
	i = check_option(cmd);
	j = i;
	if (msh->pip)
	{
		ft_echo_pipe(msh, cmd, i, j);
		return ;
	}
	while (cmd[i])
	{
		if (i > j)
			write(fd, " ", 1);
		write(fd, cmd[i], ft_strlen(cmd[i]));
		i++;
	}
	if (check_option(cmd) == 1)
		write(fd, "\n", 1);
}

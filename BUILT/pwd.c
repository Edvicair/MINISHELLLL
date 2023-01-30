/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:21:58 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/30 11:34:54 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_msh *msh)
{
	char	*pwd;
	int		fd;

	fd = 1;
	pwd = malloc(sizeof(char) * 200);
	if (!pwd)
		return ;
	if (msh->out)
		fd = msh->out;
	pwd = getcwd(pwd, 200);
	if (!pwd)
		return ;
	else if (msh->pip)
	{
		write(msh->fd[1], pwd, ft_strlen(pwd));
		write(msh->fd[1], "\n", 1);
	}
	else
	{
		write(fd, pwd, ft_strlen(pwd));
		write(fd, "\n", 1);
	}
	free(pwd);
}

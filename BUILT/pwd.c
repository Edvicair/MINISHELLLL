/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:21:58 by edvicair          #+#    #+#             */
/*   Updated: 2022/12/14 01:42:09 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_msh *msh)
{
	char	*pwd;
	int	fd;

	fd = 1;
	pwd = malloc(sizeof(char) * 200);
	if (msh->out)
		fd = msh->out;
	if (!pwd)
		printf("error pwd\n");
	pwd = getcwd(pwd, 200);
	if (!pwd)
		printf("error\n");
	else
	{
		write(fd, pwd, ft_strlen(pwd));
		write(fd, "\n", 1);
	}
}

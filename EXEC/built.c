/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:39:27 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/29 08:15:40 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_built(t_msh *msh, char **cmd)
{
	if (cmd[0] && (!ft_strncmp(cmd[0], "cd", 3)
			|| !ft_strncmp(cmd[0], "exit", 5)))
		return (1);
	else if (cmd[0] && (!ft_strncmp(cmd[0], "echo", 5)
			|| !ft_strncmp(cmd[0], "pwd", 4)))
		return (1);
	else if (cmd[0] && (!ft_strncmp(cmd[0], "env", 4)
			|| !ft_strncmp(cmd[0], "getenv", 7)))
		return (1);
	else if (cmd[0] && (!ft_strncmp(cmd[0], "export", 7)
			|| !ft_strncmp(cmd[0], "unset", 6)))
		return (1);
	return (0);
}

void	exec_built(t_msh *msh, char **cmd)
{
	if (msh->pip == 0)
	{
		if (cmd[0] && !ft_strncmp(cmd[0], "cd", 3))
			ft_cd(msh, cmd);
		else if (cmd[0] && !ft_strncmp(cmd[0], "unset", 6))
			ft_unset(msh, cmd);
		if (cmd[0] && !ft_strncmp(cmd[0], "exit", 5))
			ft_exit(msh, g_value_exit);
	}
	if (cmd[0] && !ft_strncmp(cmd[0], "pwd", 4))
		ft_pwd(msh);
	else if (cmd[0] && !ft_strncmp(cmd[0], "env", 4))
		ft_env(msh);
	else if (cmd[0] && !ft_strncmp(cmd[0], "echo", 5))
		ft_echo(msh, cmd);
	else if (cmd[0] && !ft_strncmp(cmd[0], "export", 7))
		ft_export(msh, cmd);
	if (msh->pip)
	{
		dup2(msh->fd[0], msh->in);
		close(msh->fd[0]);
		close(msh->fd[1]);
	}
}

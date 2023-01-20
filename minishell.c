/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:39:31 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/20 08:42:47 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built(t_msh *msh, char **cmd)
{
	if (cmd[0] && (!ft_strncmp(cmd[0], "cd", 3) || !ft_strncmp(cmd[0], "exit", 5)))
		return (1);
	else if (cmd[0] && (!ft_strncmp(cmd[0], "echo", 5) || !ft_strncmp(cmd[0], "pwd", 4)))
		return (1);
	else if (cmd[0] && (!ft_strncmp(cmd[0], "env", 4) || !ft_strncmp(cmd[0], "getenv", 7)))
		return (1);
	else if (cmd[0] && (!ft_strncmp(cmd[0], "export", 7) || !ft_strncmp(cmd[0], "unset", 6)))
		return (1);
	return (0);
}

void	exec_built(t_msh *msh, char **cmd, int stin)
{
	if (msh->pip == 0)
	{
		if (cmd[0] && !ft_strncmp(cmd[0], "cd", 3))
			ft_cd(msh, cmd);
		else if (cmd[0] && !ft_strncmp(cmd[0], "unset", 6))
			ft_unset(msh, cmd);
		if (cmd[0] && !ft_strncmp(cmd[0], "exit", 5))
			ft_exit(msh, stin);
	}
	if (cmd[0] && !ft_strncmp(cmd[0], "pwd", 4))
		ft_pwd(msh);
	else if (cmd[0] && !ft_strncmp(cmd[0], "env", 4))
		ft_env(msh);
	else if (cmd[0] && !ft_strncmp(cmd[0], "echo", 5))
		ft_echo(msh, cmd);
	else if (cmd[0] && !ft_strncmp(cmd[0], "export", 7))
		ft_export(msh, cmd);
}

void	ft_cmd(t_msh *msh)
{
	t_token *cpy;
	t_redir *redir_cpy;
	int nb;
	int i;

	i = 0;
	cpy = msh->token;
	nb = msh->pip;
	msh->stin = dup(0);
	msh->tab = (int *)malloc(sizeof(int) * (msh->pip + 1));
	if (!msh->tab)
		return;
	while (msh->pip >= 0)
	{
		if (pipe(msh->fd))
			break;
		ft_check_redirection(msh);
	 	if (is_built(msh, cpy->cmd))
	 		exec_built(msh, cpy->cmd, msh->stin);
		else
		{
			one_child(msh, cpy, i, msh->stin);
			if (cpy->child && msh->pip)
			{
				dup2(msh->fd[0], 0);
				close(msh->fd[0]);
				close(msh->fd[1]);			
			}
			i++;
		}
		if (msh->pip)
			cpy = cpy->next;
		msh->pip--;
	}
	close(msh->fd[0]);
	close(msh->fd[1]);
	while (i > 0)
		waitpid(msh->tab[--i], NULL, 0);
	dup2(msh->stin, 0);
	close(msh->stin);
	msh->pip = nb;
	ft_free_token(msh, msh->token);
	free(msh->tab);
}

int	main(int ac, char **av, char **env)
{
	t_msh	msh;
	t_env	*cpy;

	ft_init_struct(&msh, env);
	while (1)
	{
		msh.line = space_chips(readline("minizboub-> "));
		if (msh.line)
		{
			add_history(msh.line);
			if (parser(&msh))
			{
				if (msh.token)
					ft_cmd(&msh);
			}
			free(msh.line);
			msh.line = NULL;
		}
		else
			break;
	}
	printf("exit\n");
	ft_exit(&msh, msh.stin);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:39:31 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/24 09:48:12 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_value_exit;

void	ft_end_cmd(t_msh *msh, int i)
{
	close(msh->fd[0]);
	close(msh->fd[1]);
	while (i > 0)
		waitpid(msh->tab[--i], NULL, 0);
	dup2(msh->stin, 0);
	close(msh->stin);
	ft_free_token(msh, msh->token);
	msh->token = NULL;
	free(msh->tab);
}

int	ft_cmd_bis(t_msh *msh, t_token *cpy, int i)
{
	if (is_built(msh, cpy->cmd))
		exec_built(msh, cpy->cmd);
	else
	{
		one_child(msh, cpy, i);
		if (cpy->child && msh->pip)
		{
			dup2(msh->fd[0], 0);
			close(msh->fd[0]);
			close(msh->fd[1]);
		}
		i++;
	}
	return (i);
}

void	ft_cmd(t_msh *msh)
{
	t_token	*cpy;
	t_redir	*redir_cpy;
	int		nb;
	int		i;

	i = 0;
	cpy = msh->token;
	nb = msh->pip;
	msh->stin = dup(0);
	msh->tab = (int *)malloc(sizeof(int) * (msh->pip + 1));
	while (msh->pip >= 0 && msh->tab)
	{
		if (pipe(msh->fd))
			break ;
		if (!ft_check_redirection(msh, cpy))
			i = ft_cmd_bis(msh, cpy, i);
		if (msh->pip)
			cpy = cpy->next;
		msh->pip--;
	}
	msh->pip = nb;
	ft_end_cmd(msh, i);
}

int	main(int ac, char **av, char **env)
{
	t_msh	msh;
	t_env	*cpy;

	ft_init_struct(&msh, env);
	g_value_exit = 0;
	while (1)
	{
		sidaction();
		msh.line = readline("minizboub-> ");
		if (msh.line)
		{
			if (parser(&msh))
			{
				if (msh.token)
					ft_cmd(&msh);
			}
			free(msh.line);
			msh.line = NULL;
		}
		else
			break ;
	}
	if (msh.token)
		ft_exit_d(&msh, g_value_exit);
	return (0);
}

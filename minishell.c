/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:39:31 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/09 09:56:05 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_in(t_redir *redir, t_msh *msh)
{
	if (redir->type == RE_G)
	{
		if (msh->in != 0)
			close(msh->in);
		msh->in = open(redir->feldup, O_RDONLY);
		printf("OPEN < IN = %d\n", msh->in);
		if (msh->in < 0)
			printf("can't open %s\n", redir->feldup);
	}
	else if (redir->type == H_DOC)
	{
		if (msh->in != 0)
			close(msh->in);
		msh->in = open(redir->feldup, O_RDONLY);
		printf("OPEN << IN = %d\n", msh->in);
		if (msh->in < 0)
			printf("can't open %s\n", redir->feldup);
	}
}

void	redir_out(t_redir *redir, t_msh *msh)
{
	if (redir->type == RE_D)
	{
		if (msh->out != 0 && msh->out != 1)
			close(msh->out);
		msh->out = open(redir->feldup, O_CREAT | O_TRUNC | O_WRONLY, 0664);
		printf("OPEN > OUT = %d\n", msh->out);
		if (msh->out < 0)
			printf("can't open %s\n", redir->feldup);
	}
	else if (redir->type == RE_DD)
	{
		if (msh->out != 0 && msh->out != 1)
			close(msh->out);
		msh->out = open(redir->feldup, O_CREAT | O_APPEND | O_WRONLY, 0664);
		printf("OPEN >> OUT = %d\n", msh->in);
		if (msh->out < 0)
				printf("can't open %s\n", redir->feldup);
	}
	
}

void	ft_check_redirection(t_msh *msh)
{
	t_redir *cpy;
	bool i;

	cpy = msh->token->redir;
	i = 0;
	if (!msh->token->redir->feldup)
		return;
	while (cpy && !i)
	{
		if (cpy->next)
		{
			redir_in(cpy, msh);
			redir_out(cpy, msh);
			cpy = cpy->next;
		}
		else
			i = 1;
	}
	if (cpy)
	{
		redir_in(cpy, msh);
		redir_out(cpy, msh);
	}
}

void	ft_cmd(t_msh *msh)
{
	ft_check_redirection(msh);
	printf("IN = %d | OUT = %d\n", msh->in, msh->out);
	if (msh->token->cmd[0] && !ft_strncmp(msh->token->cmd[0], "cd", 3))
		ft_cd(msh);
	else if (msh->token->cmd[0] && !ft_strncmp(msh->token->cmd[0], "pwd", 4))
		ft_pwd(msh);
	else if (msh->token->cmd[0] && !ft_strncmp(msh->token->cmd[0], "env", 4))
		ft_env(msh);
	else if (msh->token->cmd[0] && !ft_strncmp(msh->token->cmd[0], "export", 7))
		ft_export(msh);
	else if (msh->token->cmd[0] && !ft_strncmp(msh->token->cmd[0], "unset", 6))
		ft_unset(msh);
	else if (msh->token->cmd[0] && !ft_strncmp(msh->token->cmd[0], "getenv", 7))
		printf("%s = %s\n", msh->token->cmd[1], ft_getenv(msh, msh->token->cmd[1]));
	else if (msh->token->cmd[0] && !ft_strncmp(msh->token->cmd[0], "echo", 5))
		ft_echo(msh);
	else if (msh->token->cmd[0] && !ft_strncmp(msh->token->cmd[0], "exit", 5))
		ft_exit(msh);
	else
		one_child(msh, msh->token->in, msh->token->out);
	ft_free_token(msh->token);
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
			printf("parser ...\n");
			if (parser(&msh))
			{
				printf("parser OK\n");
				if (msh.token && !msh.pip)
					ft_cmd(&msh);
				waitpid(msh.token->child, NULL, 0);
			}
			free(msh.line);
		}
		else
			break;
	}
	printf("exit\n");
	free(msh.line);
	return (0);
}

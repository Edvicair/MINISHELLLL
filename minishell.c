/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:39:31 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/05 16:41:25 by edvicair         ###   ########.fr       */
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
		printf("%d\n", msh->in);
		if (msh->in < 0)
			printf("111can't open %s\n", redir->feldup);
	}
	else if (redir->type == H_DOC)
	{
		if (msh->in != 0)
			close(msh->in);
		msh->in = open(redir->feldup, O_RDONLY);
		if (msh->in < 0)
			printf("can't open %s\n", redir->feldup);
	}
}

void	redir_out(t_redir *redir, t_msh *msh)
{
	if (redir->type == RE_D)
	{
		if (msh->out != 0)
			close(msh->out);
		msh->out = open(redir->feldup, O_CREAT | O_TRUNC | O_WRONLY, 0664);
		if (msh->out < 0)
			printf("can't open %s\n", redir->feldup);
	}
	else if (redir->type == RE_DD)
	{
		if (msh->out != 0)
			close(msh->out);
		msh->out = open(redir->feldup, O_CREAT | O_APPEND | O_WRONLY, 0664);
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
	{
		int i = 0;
		while(msh->token->cmd[i])
		{
			printf("cmd[%d] = %s\n", i, msh->token->cmd[i]);
			i++;
		}
		one_child(msh, msh->token->in, msh->token->out);
	}
	ft_free_token(msh->token);
}

int	main(int ac, char **av, char **env)
{
	t_msh	msh;
	t_env	*cpy;

	ft_init_struct(&msh, env);
	while (1)
	{
		msh.line = readline("minizboub-> ");
		if (msh.line)
		{
			add_history(msh.line);
			parser(&msh);
			if (msh.token && !msh.pip)
				ft_cmd(&msh);
			// if (msh.token && msh->pip)
			// 	ft_cmd_pipe(&msh);
		//	ft_free_double(msh.token->cmd);
			free(msh.line);
		}
		else
			break;
	}
	//printf("exit\n");
	free(msh.line);
	return (0);
}

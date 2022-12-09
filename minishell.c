/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:39:31 by edvicair          #+#    #+#             */
/*   Updated: 2022/12/08 10:29:04 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_redirection(t_msh *msh)
{
	t_redir *cpy;
	int in;
	int out;

	cpy = msh->token->redir;
	while (cpy && cpy->next)
	{
		if (cpy->type == RE_G)
			msh->in = open(cpy->feldup, O_RDONLY);
		else if (cpy->type == RE_D)
			msh->out = open(cpy->feldup, O_WRONLY | O_CREAT | O_APPEND, 0664);
		else if (cpy->type == RE_DD)
			msh->out = open(cpy->feldup, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		// else if (cpy->type == H_DOC)
		// 	msh->in = here_doc();
		if (msh->in == -1 || msh->out == -1)
		{
			perror("Can't open\n");
			// FAUT FREEE
		}
	}
}

void	ft_cmd(t_msh *msh)
{
//	ft_check_redirection(msh);
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
		printf("else cmd\n");
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
	printf("exit\n");
	free(msh.line);
	return (0);
}

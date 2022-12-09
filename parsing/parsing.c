/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motaouss <motaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:31:52 by motaouss          #+#    #+#             */
/*   Updated: 2022/11/29 05:43:46 by motaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	token_error(char *line)
{
	//if ((pipe_error(line)))
	//	return (1);
	if ((is_quote(line)))
		return (1);
	return (0);
}

void	parser(t_msh *msh)
{
	int	i;
	
	i = 0;
	if ((token_error(msh->line)))
		printf("Syntax Error\n");
	else
	{
		
		msh->token = ft_fill_token(msh);
	}
}

/*

redir struct
heredoc > feldup = delimitateur
> feldup = nom de fichier


pipe error : rien avant | rien apres | chevron avant 

chevron ereur de syntaxe <>  ><
Si chevron en dernier caractere sans compter les whitespace 
Triple chevron erreur de sytaxe
Chevron espace chevron erreur de syntaxe



Tous les whitespace en dehors des quote tu les transforme en  32 donc espace 

*/
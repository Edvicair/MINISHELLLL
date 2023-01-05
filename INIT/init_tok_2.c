/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tok_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:18:12 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/04 13:27:19 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


t_token	*ft_fill_token(t_msh *msh)
{
	char	**pipe;
	t_token	*token;
	int		i;

	i = 0;
	token = NULL;
	msh->pip = ft_strshr(msh->line, '|');
	pipe = ft_split(msh->line, '|');
	if (!pipe[i])
		return (token);
	while (pipe[i])
	{
		ft_token_add_back(&token, ft_token_new(msh, pipe[i]));
		i++;
	}
	ft_free_double(pipe);
	return (token);
}

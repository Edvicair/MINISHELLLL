/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:10:19 by edvicair          #+#    #+#             */
/*   Updated: 2021/01/09 16:01:36 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*buya;

	buya = (t_list *)malloc(sizeof(t_list));
	if (!buya)
		return (NULL);
	buya->content = content;
	buya->next = 0;
	return (buya);
}

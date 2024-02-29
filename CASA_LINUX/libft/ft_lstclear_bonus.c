/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:36:00 by jocorrea          #+#    #+#             */
/*   Updated: 2023/01/22 16:39:15 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*item;

	if (!lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		item = tmp->next;
		del(tmp->content);
		free(tmp);
		tmp = item;
	}
	*lst = NULL;
}

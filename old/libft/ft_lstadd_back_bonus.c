/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:29:05 by jocorrea          #+#    #+#             */
/*   Updated: 2023/01/22 16:34:24 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = (*lst);
	if ((*lst))
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	if (!(*lst))
		((*lst) = new);
}

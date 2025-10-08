/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:50:38 by jocorrea          #+#    #+#             */
/*   Updated: 2023/01/28 13:45:01 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*tmp;
	int		i;

	tmp = (char *)malloc((ft_strlen(s) + 1));
	i = 0;
	if (tmp)
	{
		while (s[i])
		{
			tmp[i] = s[i];
			i++;
		}
		tmp[i] = '\0';
	}
	return (tmp);
}

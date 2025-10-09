/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:08:54 by jocorrea          #+#    #+#             */
/*   Updated: 2023/01/14 16:10:21 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str, const char *str2, size_t c)
{
	size_t			i;
	unsigned int	diff;

	diff = 0;
	i = 0;
	while ((str[i] != '\0') && (str2[i] != '\0')
		&& (diff == 0) && (i < c))
	{
		diff = (unsigned char)str[i] - (unsigned char)str2[i];
		i++;
	}
	if ((diff == 0) && (i < c))
		diff = (unsigned char)str[i] - (unsigned char)str2[i];
	return (diff);
}

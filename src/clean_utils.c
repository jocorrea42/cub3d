/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:30:59 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/08/30 18:04:21 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_array(void *array)
{
	int		i;
	char	**cast;

	cast = (char **)array;
	i = 0;
	if (cast != NULL)
	{
		while (cast[i] != NULL)
		{
			free(cast[i]);
			i++;
		}
		free(cast);
		cast = NULL;
	}
}

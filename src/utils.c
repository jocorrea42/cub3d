/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyela <anyela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:43:43 by anyela            #+#    #+#             */
/*   Updated: 2024/03/04 11:52:16 by anyela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	r_angle(int angle)
{
	return ((angle * S_W) / 60);
}

double	fcos(int angle)
{
	static double	fcos[360 * S_W / 60];
	int		i;

	if (fcos[r_angle(0)] > 1.0)
		return (fcos[angle]);
	i = 0;
	while (i < r_angle(360))
	{
		fcos[i] = cos(i * M_PI / r_angle(180)) + 0.1;
		i++;
	}
	return (fcos[angle]);
}
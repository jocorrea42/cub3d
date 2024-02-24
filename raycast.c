/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:16:37 by jocorrea          #+#    #+#             */
/*   Updated: 2024/02/24 17:48:30 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	r_angle(int angle)
{
	return ((angle * W) / 60);
}

double	fcos(int angle)
{
	static double	fcos[360 * W / 60];
	int		i;

	if (fcos[r_angle(0)] > 1.0)
		return (fcos[angle]);
	i = 0;
	while (i < r_angle(360))
	{
		fcos[i] = cos(i * PI / r_angle(180)) + 0.00001;
		i++;
	}
	return (fcos[angle]);
}

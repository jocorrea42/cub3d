/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:43:43 by anyela            #+#    #+#             */
/*   Updated: 2024/03/16 14:02:51 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

int	unit_circle(float angle, char c)
{
	if (c == 'x' && (angle > 0 && angle < M_PI))
		return (1);
	else if (c == 'y' && (angle > (M_PI_2) && angle < (3 * M_PI_2)))
		return (1);
	return (0);
}

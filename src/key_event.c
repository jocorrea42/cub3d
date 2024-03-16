/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyela <anyela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:47:19 by anyela            #+#    #+#             */
/*   Updated: 2024/02/28 09:50:00 by anyela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "keys.h"

int	read_keys(int key_pressed, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (key_pressed == DOWN_LINUX || key_pressed == DOWN_MAC
		|| key_pressed == S_LINUX || key_pressed == S_MAC)
		return (cub->ply->direction = DOWN);
	else if (key_pressed == UP_LINUX || key_pressed == UP_MAC
		|| key_pressed == W_LINUX || key_pressed == W_MAC)
		return (cub->ply->direction = UP);
	else if (key_pressed == D_LINUX || key_pressed == D_MAC)
		return (cub->ply->direction = RIGHT);
	else if (key_pressed == A_LINUX || key_pressed == A_MAC)
		return (cub->ply->direction = LEFT);
	else if (key_pressed == LEFT_LINUX || key_pressed == LEFT_MAC)
		return (cub->ply->rot = -1);
	else if (key_pressed == RIGHT_LINUX || key_pressed == RIGHT_MAC)
		return (cub->ply->rot = 1);
	else if (key_pressed == ESC_LINUX || key_pressed == ESC_MAC)
		exit_win();
	return (0);
}

void	hook(t_cub *mlx)
{
	if (mlx->ply->rot)
		rotate_player(mlx->ply);
	if (mlx->ply->direction != NONE)
		general_move_player(mlx);
}

int	exit_win(void)
{
	exit(EXIT_SUCCESS);
}

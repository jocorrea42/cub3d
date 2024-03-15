/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyela <anyela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:50:55 by anyela            #+#    #+#             */
/*   Updated: 2024/02/28 10:00:22 by anyela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_player *player)
{
	if (player->rot == 1)
	{
		player->angle += ROTATION_SPEED;
		if (player->angle > 2 * M_PI)
			player->angle -= 2 * M_PI;
	}
	else
	{
		player->angle -= ROTATION_SPEED;
		if (player->angle < 0)
			player->angle += 2 * M_PI;
	}
	player->rot = 0;
}

void	general_move_player(t_cub *mlx)
{
	if (mlx->ply->direction == RIGHT)
		move_player(mlx, -sin(mlx->ply->angle) * mlx->ply->speed,
			cos(mlx->ply->angle) * mlx->ply->speed);
	if (mlx->ply->direction == LEFT)
		move_player(mlx, sin(mlx->ply->angle) * mlx->ply->speed,
			-cos(mlx->ply->angle) * mlx->ply->speed);
	if (mlx->ply->direction == UP)
		move_player(mlx, cos(mlx->ply->angle) * mlx->ply->speed,
			sin(mlx->ply->angle) * mlx->ply->speed);
	if (mlx->ply->direction == DOWN)
		move_player(mlx, -cos(mlx->ply->angle) * mlx->ply->speed,
			-sin(mlx->ply->angle) * mlx->ply->speed);
	mlx->ply->direction = NONE;
}

void	move_player(t_cub *mlx, double move_x, double move_y)
{
	int	new_x;
	int	new_y;

	new_x = roundf(mlx->ply->plyr_x + move_x);
	new_y = roundf(mlx->ply->plyr_y + move_y);
	if (mlx->dt->map2d[new_y / *mlx->tile][new_x / *mlx->tile] != '1'
		&& (mlx->dt->map2d[new_y / *mlx->tile]
		[mlx->ply->plyr_x / *mlx->tile] != '1'
		&& mlx->dt->map2d[mlx->ply->plyr_y / *mlx->tile]
		[new_x / *mlx->tile] != '1'))
	{
		mlx->ply->plyr_x = new_x;
		mlx->ply->plyr_y = new_y;
	}
}

void	ft_exit(t_cub *mlx)
{
	int	i;

	i = 0;
	while (mlx->dt->map2d[i])
		free(mlx->dt->map2d[i++]);
	free(mlx->dt->map2d);
	free(mlx->dt);
	free(mlx->ply);
	free(mlx->ray);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img->img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	printf("Game closed\n");
	exit(0);
}

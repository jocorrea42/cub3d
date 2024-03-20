/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:50:55 by anyela            #+#    #+#             */
/*   Updated: 2024/03/16 14:10:34 by jocorrea         ###   ########.fr       */
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
	if (mlx->pl->direction == RIGHT)
		move_player(mlx, -sin(mlx->pl->angle) * mlx->pl->speed,
			cos(mlx->pl->angle) * mlx->pl->speed);
	if (mlx->pl->direction == LEFT)
		move_player(mlx, sin(mlx->pl->angle) * mlx->pl->speed,
			-cos(mlx->pl->angle) * mlx->pl->speed);
	if (mlx->pl->direction == UP)
		move_player(mlx, cos(mlx->pl->angle) * mlx->pl->speed,
			sin(mlx->pl->angle) * mlx->pl->speed);
	if (mlx->pl->direction == DOWN)
		move_player(mlx, -cos(mlx->pl->angle) * mlx->pl->speed,
			-sin(mlx->pl->angle) * mlx->pl->speed);
	mlx->pl->direction = NONE;
}

void	move_player(t_cub *mlx, double move_x, double move_y)
{
	int	new_x;
	int	new_y;

	new_x = roundf(mlx->pl->pl_x + move_x);
	new_y = roundf(mlx->pl->pl_y + move_y);
	if (cast_direction_ray(mlx, new_x, new_y))
	{
		mlx->pl->pl_x = new_x;
		mlx->pl->pl_y = new_y;
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
	free(mlx->pl);
	free(mlx->ray);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img->img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	printf("Game closed\n");
	exit(0);
}

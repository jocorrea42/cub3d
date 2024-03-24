/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:55:44 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/03/24 17:42:33 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mini_config(t_cub *mlx)
{
	mlx->mp.tile_x = mlx->dt->h_map * 10;
	mlx->mp.tile_y = mlx->dt->w_map * 10;
	if (mlx->mp.tile_y > S_W / 4)
	{
		mlx->mp.factor_y = mlx->mp.tile_y / (S_W / 4);
		mlx->mp.tile_y = S_W / 4;
		mlx->mp.tile_x = (int)mlx->mp.tile_x / mlx->mp.factor_y;
	}
	if (mlx->mp.tile_x > S_H / 4)
	{
		mlx->mp.factor_x = mlx->mp.tile_x / (S_W / 4);
		mlx->mp.tile_x = S_H / 4;
		mlx->mp.tile_y = (int)mlx->mp.tile_y / mlx->mp.factor_x;
	}
	mlx->mp.factor_x = mlx->mp.tile_x / (mlx->dt->h_map);
	mlx->mp.factor_y = mlx->mp.tile_y / (mlx->dt->w_map);
	mlx->mp.y_p = mlx->pl->pl_x / *mlx->tile;
	mlx->mp.x_p = mlx->pl->pl_y / *mlx->tile;
}

void	minidraw(t_cub *mlx)
{
	mlx->mp.i = -1;
	while (++mlx->mp.i < mlx->mp.tile_x)
	{
		mlx->mp.j = -1;
		while (++mlx->mp.j < mlx->mp.tile_y)
		{
			mlx->mp.x = (mlx->mp.i / mlx->mp.factor_x);
			mlx->mp.y = (mlx->mp.j / mlx->mp.factor_y);
			if (mlx->mp.x == mlx->mp.x_p && mlx->mp.y == mlx->mp.y_p)
				my_mlx_pixel_put(mlx, mlx->mp.j, mlx->mp.i, 0xABCDEF);
			else if (mlx->mp.x < mlx->dt->h_map && mlx->mp.y < mlx->dt->w_map
				&& mlx->dt->map2d[mlx->mp.x][mlx->mp.y] == '1')
				my_mlx_pixel_put(mlx, mlx->mp.j, mlx->mp.i, 0xFF0000);
			else if (mlx->mp.x < mlx->dt->h_map && mlx->mp.y < mlx->dt->w_map
				&& mlx->dt->map2d[mlx->mp.x][mlx->mp.y] == '2')
				my_mlx_pixel_put(mlx, mlx->mp.j, mlx->mp.i, 0x00FF00);
			else if (mlx->mp.x < mlx->dt->h_map && mlx->mp.y < mlx->dt->w_map
				&& mlx->dt->map2d[mlx->mp.x][mlx->mp.y] == '3')
				my_mlx_pixel_put(mlx, mlx->mp.j, mlx->mp.i, 0x0000FF);
			else
				my_mlx_pixel_put(mlx, mlx->mp.j,
					mlx->mp.i, *mlx->textures->floor);
		}
	}
}

void	minimap(t_cub *mlx)
{
	mini_config(mlx);
	if (mlx->dt->map2d[mlx->mp.x_p][mlx->mp.y_p] == '1')
	{
		mlx->mp.x_p = mlx->old_x;
		mlx->mp.y_p = mlx->old_y;
	}
	else
	{
		mlx->old_x = mlx->mp.x_p;
		mlx->old_y = mlx->mp.y_p;
	}
	minidraw(mlx);
}

int	mouse_move(int x, int y, void *param)
{
	t_cub	*mlx;

	(void)y;
	mlx = (t_cub *) param;
	if (x > S_W / 2)
		mlx->pl->rot = 1;
	else if (x < S_W / 2)
		mlx->pl->rot = -1;
	mlx->pl->mouse_rot = 1;
	mlx_mouse_move(mlx->mlx_ptr, mlx->win_ptr, S_W / 2, S_H / 2);
	return (0);
}

void	centered_string(void *mlx, void *win, int color, char *string)
{
	int	size;
	int	x;
	int	y;

	size = ft_strlen(string);
	x = S_W / 2 - (size / 2) * 10;
	y = S_H - S_H / 8;
	mlx_string_put(mlx, win, x, y, color, string);
}

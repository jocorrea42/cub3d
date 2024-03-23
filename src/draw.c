/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:11:39 by jocorrea          #+#    #+#             */
/*   Updated: 2024/03/23 17:23:22 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_ceiling(t_cub *mlx, int ray, int t_pix, int b_pix)
{
	int	i;

	i = b_pix;
	while (i < S_H)
		my_mlx_pixel_put(mlx, ray, i++, *mlx->textures->floor);
	i = -1;
	while (++i < t_pix)
		my_mlx_pixel_put(mlx, ray, i, *mlx->textures->ceiling);
}

t_img	*get_texture(t_cub *mlx)
{
	mlx->ray->ray_angle = nor_angle(mlx->ray->ray_angle);
	if (mlx->ray->flag == 0)
	{
		if (mlx->ray->ray_angle > M_PI_2 && mlx->ray->ray_angle < 3 * M_PI_2)
			return (mlx->textures->west);
		return (mlx->textures->east);
	}
	else
	{
		if (mlx->ray->ray_angle > 0 && mlx->ray->ray_angle < M_PI)
			return (mlx->textures->south);
		else
			return (mlx->textures->north);
	}
}

double	get_x_o(t_cub *mlx, t_img *current_texture)
{
	double	x_o;

	x_o = mlx->ray->vert_y;
	if (mlx->ray->flag == 1)
		x_o = mlx->ray->horiz_x;
	return (fmodf(x_o * (current_texture->w / *mlx->tile),
			current_texture->w));
}

void minimap(t_cub *mlx)
{
	int i;
	int j;
	double factor_x;
	double factor_y;
	int x_m;
	int x_p;
	int y_m;
	int y_p;
	int tile_x;
	int tile_y;


	tile_x =  mlx->dt->h_map * 10;
	tile_y = mlx->dt->w_map *10;
	factor_x = tile_x / (mlx->dt->h_map);
	factor_y = tile_y / (mlx->dt->w_map);
	y_p = mlx->pl->pl_x / *mlx->tile;
	x_p = mlx->pl->pl_y / *mlx->tile;
	if ( mlx->dt->map2d[x_p][y_p] == '1')
	{
		x_p = mlx->old_x;
		y_p = mlx->old_y;
	}
	else
	{
		mlx->old_x = x_p;
		mlx->old_y = y_p;
	}
//	printf("x_m=%d, y_m=%d\n", x_m, y_m);
	i = -1;
	while (++i < tile_x)
	{
		j = -1;
		while (++j < tile_y)
		{
			x_m = (i  / factor_x);
			y_m = (j / factor_y);
			if (x_m == x_p && y_m == y_p)
				my_mlx_pixel_put(mlx, j, i, 0xFFFFFF + (int)(mlx->pl->angle));
			else if (x_m < mlx->dt->h_map && y_m < mlx->dt->w_map && mlx->dt->map2d[x_m][y_m] == '1')
				my_mlx_pixel_put(mlx, j, i, 0xFF0000);
			else
				my_mlx_pixel_put(mlx, j, i, 0);
		}
	}
}

void	draw_wall(t_cub *mlx, int t_pix, int b_pix, double wall_h)
{
	double			x_o;
	double			y_o;
	unsigned int	*img_addr;
	double			factor;
	t_img			*current_texture;

	current_texture = get_texture(mlx);
	img_addr = (unsigned int *)current_texture->addr;
	x_o = get_x_o(mlx, current_texture);
	factor = (double)current_texture->h / wall_h;
	y_o = (t_pix - (S_H / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		my_mlx_pixel_put(mlx, mlx->ray->index, t_pix,
			(img_addr[(int)y_o * current_texture->w + (int)x_o]));
		y_o += factor;
		t_pix++;
	}
}

void	render_wall(t_cub *mlx, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	mlx->ray->distance *= cos(nor_angle(mlx->ray->ray_angle - mlx->pl->angle));
	wall_h = (*mlx->tile / mlx->ray->distance) * ((S_W / 2)
			/ tan(mlx->pl->fov_rd / 2));
	b_pix = (S_H / 2) + (wall_h / 2);
	t_pix = (S_H / 2) - (wall_h / 2);
	if (b_pix > S_H)
		b_pix = S_H;
	if (t_pix < 0)
		t_pix = 0;
	mlx->ray->index = ray;
	if (wall_h > 0)
		draw_wall(mlx, t_pix, b_pix, wall_h);
	draw_floor_ceiling(mlx, ray, t_pix, b_pix);
}

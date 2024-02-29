/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyela <anyela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:43:53 by jocorrea          #+#    #+#             */
/*   Updated: 2024/02/28 09:51:49 by anyela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img new_program(int w, int h, char *str)
{
	t_img img;

	img.mlx_ptr = mlx_init();
	img.win_ptr = mlx_new_window(img.mlx_ptr, w, h, str);
	img.img_ptr = mlx_new_image(img.mlx_ptr, w, h);
	img.addr = mlx_get_data_addr(img.img_ptr, &(img.bpp), &(img.l_len), &(img.endian));
	img.w = w;
	img.h = h;
	return (img);
}

void my_mlx_pixel_put(t_cub *cub, int x, int y, int color) // put the pixel
{
	char *dst;

	if (x >= 0 && y >= 0 && x < cub->img.w && y < cub->img.h)
	{
		dst = cub->img.addr + (y * cub->img.l_len + x * (cub->img.bpp / 8));
		*(unsigned int *)dst = color;
	} // put the pixel
}

void draw_floor_ceiling(t_cub *mlx, int ray, int t_pix, int b_pix) // draw the floor and the ceiling
{
	int i;

	i = b_pix;
	while (i < S_H)
		my_mlx_pixel_put(mlx, ray, i++, 0x3C302A); // floor
	i = -1;
	while (++i < t_pix)
		my_mlx_pixel_put(mlx, ray, i, 0x00BFFF); // ceiling
}

int get_color(t_cub *mlx) // get the color of the wall
{
	mlx->ray->ray_angle = nor_angle(mlx->ray->ray_angle); // normalize the angle
	if (mlx->ray->flag == 0)
	{
		if (mlx->ray->ray_angle > PI / 2 && mlx->ray->ray_angle < 3 * (PI / 2))
			return (0x800000); // west wall
		else
			return (0x3B7861); // east wall
	}
	else
	{
		if (mlx->ray->ray_angle > 0 && mlx->ray->ray_angle < PI)
			return (0x5E4B41); // south wall
		else
			return (0x808080); // north wall
	}
}

void draw_wall(t_cub *mlx, int ray, int t_pix, int b_pix) // draw the wall
{
	int color;

	color = get_color(mlx);
	while (t_pix < b_pix)
		my_mlx_pixel_put(mlx, ray, t_pix++, color);
}

void render_wall(t_cub *mlx, int ray) // render the wall
{
	double wall_h;
	double b_pix;
	double t_pix;

	mlx->ray->distance *= cos(nor_angle(mlx->ray->ray_angle - mlx->ply->angle));			 // fix the fisheye
	wall_h = (TILE_SIZE / mlx->ray->distance) * ((S_W / 2) / tan(mlx->ply->fov_rd / 2)); // get the wall height
	b_pix = (S_H / 2) + (wall_h / 2);													 // get the bottom pixel
	t_pix = (S_H / 2) - (wall_h / 2);													 // get the top pixel
	if (b_pix > S_H)																	 // check the bottom pixel
		b_pix = S_H;
	if (t_pix < 0) // check the top pixel
		t_pix = 0;
	draw_wall(mlx, ray, t_pix, b_pix);			// draw the wall
	draw_floor_ceiling(mlx, ray, t_pix, b_pix); // draw the floor and the ceiling
}

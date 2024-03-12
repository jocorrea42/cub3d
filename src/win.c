/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyela <anyela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:43:53 by jocorrea          #+#    #+#             */
/*   Updated: 2024/03/07 09:46:19 by anyela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img *new_program(int w, int h, char *str)
{
	t_img *img;

	img = safe_calloc(1, sizeof(t_img));
	img->mlx_ptr = mlx_init();
	img->win_ptr = mlx_new_window(img->mlx_ptr, w, h, str);
	img->img_ptr = mlx_new_image(img->mlx_ptr, w, h);
	img->addr = mlx_get_data_addr(img->img_ptr, &(img->bpp), &(img->l_len), &(img->endian));
	img->w = w;
	img->h = h;
	return (img);
}

void my_mlx_pixel_put(t_cub *cub, int x, int y, int color) // put the pixel
{
	char *dst;

	if (x >= 0 && y >= 0 && x < cub->img->w && y < cub->img->h)
	{
		dst = cub->img->addr + (y * cub->img->l_len + x * (cub->img->bpp / 8));
		*(unsigned int *)dst = color;
	} // put the pixel
}

void draw_floor_ceiling(t_cub *mlx, int ray, int t_pix, int b_pix) // draw the floor and the ceiling
{
	int i;

	i = b_pix;
	while (i < S_H)
		my_mlx_pixel_put(mlx, ray, i++, mlx->textures->floor); // floor
	i = -1;
	while (++i < t_pix)
		my_mlx_pixel_put(mlx, ray, i, mlx->textures->ceiling); // ceiling
}

t_img *get_texture(t_cub *mlx) // get the texture of the wall
{
	mlx->ray->ray_angle = nor_angle(mlx->ray->ray_angle); // normalize the angle
	if (mlx->ray->flag == 0)
	{
		if (mlx->ray->ray_angle > M_PI / 2 && mlx->ray->ray_angle < 3 * (M_PI / 2))
			return (mlx->textures->west); // west wall
		else
			return (mlx->textures->east); // east wall
	}
	else
	{
		if (mlx->ray->ray_angle > 0 && mlx->ray->ray_angle < M_PI)
			return (mlx->textures->south); // south wall
		else
			return (mlx->textures->north); // north wall
	}
}

double get_x_o(t_cub *mlx, t_img *current_texture)
{
	double x_o;
// se chaquea la insidencia del rayo
	if (mlx->ray->flag == 1)//calculo de relacion horizontal
		x_o = (int)fmodf((mlx->ray->horiz_x * (current_texture->w / TILE_SIZE)), current_texture->w);
	else// calculo de relacion vertical
		x_o = (int)fmodf((mlx->ray->vert_y *(current_texture->w / TILE_SIZE)),current_texture->w);
	return (x_o);
}

void draw_wall(t_cub *mlx, int t_pix, int b_pix, double wall_h) // draw the wall
{
	double x_o;//x de la textura
	double y_o;//y de la textura
	unsigned int *img_addr;//datos de la imagen, no es necesario podria utilizarse la propia variable mlx
	double factor;
	t_img *current_texture;

	current_texture = get_texture(mlx);
	img_addr = (unsigned int *)current_texture->addr;
	factor = (double)current_texture->h / wall_h;
	x_o = get_x_o(mlx, current_texture);//seria la linea de la textura correspondiente en relacion a la imagen o sea donde estaria 
	//ray correspondiente en la textura segun el ancho del bloque de pared
	y_o = (t_pix - (S_H / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		my_mlx_pixel_put(mlx, mlx->ray->index, t_pix, (img_addr[(int)y_o * current_texture->w + (int)x_o]));
		y_o += factor;
		t_pix++;
	}
}

void render_wall(t_cub *mlx, int ray)
{
	double wall_h;
	double b_pix;
	double t_pix;

	mlx->ray->distance *= cos(nor_angle(mlx->ray->ray_angle - mlx->ply->angle));// fix the fisheye
	wall_h = (TILE_SIZE / mlx->ray->distance) * ((S_W / 2) / tan(mlx->ply->fov_rd / 2));//get the wall height
	b_pix = (S_H / 2) + (wall_h / 2);//get bottom pixel
	t_pix = (S_H / 2) - (wall_h / 2);//get top pixel
	if (b_pix > S_H)//check bottom edge 
		b_pix = S_H;
	if (t_pix < 0)//check top edge
		t_pix = 0;
	mlx->ray->index = ray;//vertical line of the wall in pixel
	// this is where you should look for the corresponding line of the texture 
	//and paint that line with the height of the wall.
	draw_wall(mlx, t_pix, b_pix, wall_h);//draw wall
	draw_floor_ceiling(mlx, ray, t_pix, b_pix);//pita el piso y el cielo, aqui se podria poner una textura para
	//el suelo
}
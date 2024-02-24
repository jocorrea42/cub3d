/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:01:08 by jocorrea          #+#    #+#             */
/*   Updated: 2024/02/24 15:15:32 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "win.h"

int get_color()
{
	return (rand() % 2147483647);
}

int read_keys(int key_pressed, void *param)
{
	t_img *img;

	img = (t_img *)param;
	if (key_pressed == ESC || !img)
		exit_win(&img->win);
	else if (key_pressed == ENTER)
		draw_square((t_square){0, 0, img->w, get_color()}, *img);
	else if (key_pressed == FOLLOW)
		*img->addr = !*img->addr;
	else if (key_pressed == COLOR)
		*img->addr = get_color();
	// else if (key_pressed == PENGUIN)
	//         penguin(*img);
	else
		return (-1);
	mlx_put_image_to_window(img->win.mlx_ptr, img->win.win_ptr, img->img_ptr, 0, 0);
	return (0);
}

int read_mouse(int button, int mouse_x, int mouse_y, void *param)
{
	int 		x;
	int 		y;
	t_img 		*img;
	t_square	s;

	img = (t_img *) param;
	if (!img)
		return (-1);
	if (mouse_x < 0 || mouse_y < 0 || mouse_x > img->w || mouse_y > img->h)
		return (2);
	x = ((mouse_x % img->w) / 20) * 20;
	y = ((mouse_y % img->h) / 20) * 20;
	s = (t_square){x, y, 20, get_color()};
	draw_square(s, *img);
	mlx_put_image_to_window(img->win.mlx_ptr, img->win.win_ptr, img->img_ptr, 0, 0);
	(void)button;
	return (0);
}

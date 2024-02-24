/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:04:33 by jocorrea          #+#    #+#             */
/*   Updated: 2024/02/24 15:11:04 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "win.h"

int main(void)
{
	/**
	 *	void	*mlx_ptr;
	 *	void	*win_ptr;
	 *
	 *	mlx_ptr = mlx_init();
	 *	if (!mlx_ptr)
	 *		return (1);
	 *	win_ptr = mlx_new_window (mlx_ptr, 300, 300, "Hello World");
	 *	if (!win_ptr)
	 *		return (2);
	 *	mlx_loop(mlx_ptr);
	t_win	win;
	t_img	image_4x4;

	win = new_program(300, 300, "New Program");
	if (!win.mlx_ptr || !win.win_ptr)
		return (1);
	image_4x4.win = win;
	image_4x4.img_ptr = mlx_new_image(win.mlx_ptr, 4, 4);
	image_4x4.addr = mlx_get_data_addr(image_4x4.img_ptr, &(image_4x4.bpp), &(image_4x4.line_len), &(image_4x4.endian));
	image_4x4.w = 4;
	image_4x4.h = 4;
	memcpy(image_4x4.addr, "s4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vf", 16*4);
	mlx_put_image_to_window (image_4x4.win.mlx_ptr, image_4x4.win.win_ptr, image_4x4.img_ptr, 10, 10);
	printf("Let's Find out what's inside our structure :D\n");
	printf("img_ptr		: [%p]\n", image_4x4.img_ptr);
	printf("bpp		: [%d]\n", image_4x4.bpp);
	printf("line_len	: [%d]\n", image_4x4.line_len);
	printf("endian		: [%d]\n", image_4x4.endian);
	printf("addr		: [%p]\n", image_4x4.addr);
	put_pixel_img(image_4x4, 150, 150, 0x00FFFFFF);
	mlx_put_image_to_window (image_4x4.win.mlx_ptr, image_4x4.win.win_ptr, image_4x4.img_ptr, 0, 0);
	mlx_put_image_to_window (image_4x4.win.mlx_ptr, image_4x4.win.win_ptr, image_4x4.img_ptr, 150, 150);
	mlx_loop(win.mlx_ptr);
	*/
	t_win	win;
	t_img	image;

	win = new_program(300, 300, "tutorial");
	if (!win.win_ptr)
		return (2);
	image = new_img(300, 300, win);
	/* Put white pixel */
	put_pixel_img(image, 150, 150, 0x00FFFFFF);
	mlx_put_image_to_window (image.win.mlx_ptr, image.win.win_ptr, image.img_ptr, 0, 0);
	draw_square((t_square){0, 0, 300, 0x00FF00}, image);
	mlx_put_image_to_window (image.win.mlx_ptr, image.win.win_ptr, image.img_ptr, 0, 0);
	mlx_hook(win.win_ptr, 17, 0, exit_win, &win);
	mlx_key_hook(win.win_ptr, read_keys, &image);
	mlx_mouse_hook(win.win_ptr, read_mouse, &image);
	mlx_loop(win.mlx_ptr);
	return (0);
}

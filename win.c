/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:43:53 by jocorrea          #+#    #+#             */
/*   Updated: 2024/02/24 17:15:02 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img new_program(int w, int h, char *str)
{
	t_img	img;

	img.mlx_ptr = mlx_init();
	img.win_ptr = mlx_new_window(img.mlx_ptr, w, h, str);
	img.img_ptr = mlx_new_image(img.mlx_ptr, w, h);
	img.addr = mlx_get_data_addr(img.img_ptr, &(img.bpp), &(img.l_len), &(img.endian));
	img.w = w;
	img.h = h;
	return (img);
}

int	exit_win(t_img *window)
{
	if (window)
		mlx_destroy_window(window->mlx_ptr, window->win_ptr);
	exit(EXIT_SUCCESS);
}

void	put_pixel_img(t_img img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < img.w && y < img.h) {
		dst = img.addr + (y * img.l_len + x * (img.bpp / 8));
		*(unsigned int *) dst = color;
	}
}

void	draw_square(t_square square, t_img img)
{
	unsigned short int	i;
	unsigned short int	j;

	i = 0;
	while (i < square.size && i + square.y < img.h)
	{
		j = 0;
		while (j < square.size && j + square.x < img.w)
		{
			put_pixel_img(img, j + square.x, i + square.y, square.color);
			j++;
		}
		i++;
	}
}

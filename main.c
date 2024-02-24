/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:19:51 by jocorrea          #+#    #+#             */
/*   Updated: 2024/02/24 17:46:50 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>
int main(void)
{
	t_cub cub;
	float	x_w;
	float y_w;
	int i = -1;
	int j;

	int x[16][16] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,0,0,0,0,0,0,200,0,0,0,0,0,0,0,1},{1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},{1,0,0,1,0,0,0,1,1,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

	cub.img = new_program(800, 800, "CUB3D");
	///cub.ply->angle = 30;
	//cub.ply->plyr_x = 300;
	//cub.ply->plyr_y = 300;
	//cub.ply->fov_rd = 10;

	x_w = cub.img.w / 16;
	y_w = cub.img.h /16;
	while (++i <= 16)
	{
		j = -1;
		while (++j <= 16)
			draw_square((t_square){(i*x_w)+i, (j*y_w)+j, x_w, x[i][j]*0xFFFFF}, cub.img);
	}
	draw_square((t_square){300, 300, 10, 0xFFB1A1}, cub.img);
	//put_pixel_img(cub.img, 150, 150, 0x00FFFF);
	mlx_put_image_to_window(cub.img.mlx_ptr, cub.img.win_ptr, cub.img.img_ptr, 0, 0);

	mlx_hook(cub.img.win_ptr, 17, 0, exit_win, &cub.img);
	// mlx_key_hook(cub.img.win_ptr, read_keys, &image);
	// mlx_mouse_hook(win.win_ptr, read_mouse, &image);
	mlx_loop(cub.img.mlx_ptr);
	return (0);
}

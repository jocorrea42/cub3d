/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyela <anyela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:47:19 by anyela            #+#    #+#             */
/*   Updated: 2024/02/28 09:50:00 by anyela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	new_file_img(char * path, t_img img) {

	int a;
	img.img_ptr = mlx_xpm_file_to_image(img.mlx_ptr, path, &img.w, &img.h);
	if (!img.img_ptr)
		a = write(2, "File could not be read\n", 23);
	else
		img.addr = mlx_get_data_addr(img.img_ptr, &(img.bpp), &(img.l_len), &(img.endian));
	(void)a;
	return (img);
}

unsigned int	get_pixel_img(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.addr
			+ (y * img.l_len) + (x * img.bpp / 8))));
}
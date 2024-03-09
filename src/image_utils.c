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

t_img	*new_file_img(char * path, t_cub *mlx) {

	t_img	*img;

	img = safe_calloc(1, sizeof(t_img));
	img->img_ptr = mlx_xpm_file_to_image(mlx->img->mlx_ptr, path, &img->w, &img->h);
	if (!img->img_ptr)
		ft_perror(EINVAL, "Cannot load image");
	else
		img->addr = mlx_get_data_addr(img->img_ptr, &(img->bpp), &(img->l_len), &(img->endian));
	return (img);
}

unsigned int	get_pixel_img(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.addr
			+ (y * img.l_len) + (x * img.bpp / 8))));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:43:53 by jocorrea          #+#    #+#             */
/*   Updated: 2024/03/16 13:15:53 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*new_program(t_cub *mlx)
{
	t_img	*img;

	img = safe_calloc(1, sizeof(t_img));
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		ft_perror(ENOMEM, "mlx init failed");
	img->img_ptr = mlx_new_image(mlx->mlx_ptr, S_W, S_H);
	img->addr = mlx_get_data_addr(img->img_ptr, &(img->bpp), &(img->l_len),
			&(img->endian));
	img->w = S_W;
	img->h = S_H;
	return (img);
}

void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color) // put the pixel
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < cub->img->w && y < cub->img->h)
	{
		dst = cub->img->addr + (y * cub->img->l_len + x * (cub->img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyela <anyela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:47:19 by anyela            #+#    #+#             */
/*   Updated: 2024/02/28 09:50:00 by anyela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//HARD CODED TO 8 SPRITES
t_sprite	*new_sprite(t_cub *mlx)
{
	t_sprite	*img;

	img = safe_calloc(1, sizeof(t_sprite));
	img->sprites = (void **) safe_calloc (8 + 1, sizeof(void *));
	img->sprites[0] = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"sprites/coll_0.xpm", &img->w, &img->h);
	img->sprites[1] = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"sprites/coll_1.xpm", &img->w, &img->h);
	img->sprites[2] = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"sprites/coll_2.xpm", &img->w, &img->h);
	img->sprites[3] = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"sprites/coll_3.xpm", &img->w, &img->h);
	img->sprites[4] = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"sprites/coll_4.xpm", &img->w, &img->h);
	img->sprites[5] = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"sprites/coll_5.xpm", &img->w, &img->h);
	img->sprites[6] = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"sprites/coll_6.xpm", &img->w, &img->h);
	img->sprites[7] = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"sprites/coll_7.xpm", &img->w, &img->h);
	img->size = 8;
	img->frame = 7;
	return (img);
}

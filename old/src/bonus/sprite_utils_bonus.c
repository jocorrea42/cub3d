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
//HARD CODED TO 5 SPRITES
t_sprite	*new_sprite(t_cub *mlx)
{
	t_sprite	*img;
	int			tmp;

	img = safe_calloc(1, sizeof(t_sprite));
	img->sprites = (void **) safe_calloc (6, sizeof(void *));
	img->sprites[0] = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"sprites/tile000.xpm", &img->w, &img->h);
	img->sprites[1] = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"sprites/tile001.xpm", &img->w, &img->h);
	img->sprites[2] = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"sprites/tile002.xpm", &img->w, &img->h);
	img->sprites[3] = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"sprites/tile003.xpm", &img->w, &img->h);
	img->sprites[4] = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"sprites/tile004.xpm", &img->w, &img->h);
	img->sprites[5] = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"sprites/bullet_hole.xpm", &tmp, &tmp);
	if (!img->sprites[0] || !img->sprites[1] || !img->sprites[2]
		|| !img->sprites[3] || !img->sprites[4] || !img->sprites[5])
		ft_perror(ENOMEM, "Failed load image");
	img->size = 5;
	img->frame = 0;
	return (img);
}

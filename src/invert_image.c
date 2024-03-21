/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invert_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:58:30 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/03/21 10:58:33 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Inverts an image horizontally along the x-axis.
 *
 * This function swaps the pixels of an image symmetrically across the vertical
 * centerline.
 *
 * Param: Pointer to a structure t_img representing the image to be inverted.
 * Return: void
 */
void	invert_image_x(t_img *img)
{
	int				i;
	int				j;
	unsigned int	first_color;
	unsigned int	last_color;

	j = 0;
	while (j < img->h)
	{
		i = 0;
		while (i < img->w / 2)
		{
			first_color = *(unsigned int *)(img->addr + (j * img->l_len
						+ i * (img->bpp / 8)));
			last_color = *(unsigned int *)(img->addr + (j * img->l_len
						+ (img->w - 1 - i) * (img->bpp / 8)));
			*(unsigned int *)(img->addr + (j * img->l_len
						+ i * (img->bpp / 8))) = last_color;
			*(unsigned int *)(img->addr + (j * img->l_len
						+ (img->w - 1 - i) * (img->bpp / 8))) = first_color;
			i++;
		}
		j++;
	}
}

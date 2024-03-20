/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyela <anyela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:47:19 by anyela            #+#    #+#             */
/*   Updated: 2024/02/28 09:50:00 by anyela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_positive_number(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	*create_new_color(char *path)
{
	char	*tok;
	char	*trim;
	int		i;
	int		*color;

	color = (int *)safe_calloc(1, sizeof(int));
	tok = ft_strtok(path, ",");
	i = 0;
	while (tok)
	{
		trim = safe_strtrim(tok, " ");
		if (i > 2 || ft_strlen(trim) > 3 || !is_positive_number(trim)
			|| ft_atoi(trim) > 255)
			ft_perror(EINVAL, "Error in RGB format");
		*color |= ft_atoi(trim) << (16 - (8 * i));
		free(trim);
		i++;
		tok = ft_strtok(NULL, ",");
	}
	if (i != 3)
		ft_perror(EINVAL, "RBG missing");
	return (color);
}

t_img	*new_file_img(char *path, t_cub *mlx)
{
	t_img	*img;

	if (ft_strcmp(".xpm", ft_strrchr(path, '.')))
		ft_perror(EINVAL, "Image must be .xpm");
	img = safe_calloc(1, sizeof(t_img));
	img->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, path, &img->w,
			&img->h);
	if (!img->img_ptr){
		printf("%s\n", path);
		ft_perror(EINVAL, "Cannot load image");
	}
	else
		img->addr = mlx_get_data_addr(img->img_ptr, &(img->bpp), &(img->l_len),
				&(img->endian));
	printf("w: %d, h: %d\n", img->w, img->h);
	if (img->h != img->w)
		ft_perror(EINVAL, "All textures must be squares");
	if (!mlx->tile)
	{
		mlx->tile = (int *)safe_calloc(1, sizeof(int));
		*mlx->tile = img->h;
	}
	if (*mlx->tile != img->h)
		ft_perror(EINVAL, "All textures must have the same size");
	return (img);
}

/* unsigned int	get_pixel_img(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.addr + (y * img.l_len) + (x * img.bpp / 8))));
} */

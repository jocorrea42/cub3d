/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:19:30 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/03/24 17:48:54 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_textures_ok(t_tex *tex)
{
	return (tex->ceiling && tex->floor && tex->north && tex->south && tex->west
		&& tex->east && tex->door);
}

void	add_texture(char *tok, char *info, t_cub *mlx)
{
	char	*tmp;

	if (!info)
		ft_perror(EINVAL, "Invalid texture - No path");
	tmp = ft_strtok(info, " ");
	if (!ft_strcmp(tok, "NO") && !mlx->textures->north)
		mlx->textures->north = new_file_img(tmp, mlx);
	else if (!ft_strcmp(tok, "SO") && !mlx->textures->south)
	{
		mlx->textures->south = new_file_img(tmp, mlx);
		invert_image_x(mlx->textures->south);
	}
	else if (!ft_strcmp(tok, "WE") && !mlx->textures->west)
	{
		mlx->textures->west = new_file_img(tmp, mlx);
		invert_image_x(mlx->textures->west);
	}
	else if (!ft_strcmp(tok, "EA") && !mlx->textures->east)
		mlx->textures->east = new_file_img(tmp, mlx);
	else if (!ft_strcmp(tok, "D") && !mlx->textures->door)
		mlx->textures->door = new_file_img(tmp, mlx);
	else
		ft_perror(EINVAL, "Invalid texture - Wrong identifier");
	if (ft_strtok(NULL, " "))
		ft_perror(EINVAL, "Invalid texture - Extra information in line");
}

void	add_color(char *tok, char *info, t_cub *mlx)
{
	if (!info)
		ft_perror(EINVAL, "Invalid color - No RGB");
	if (!ft_strcmp(tok, "C") && !mlx->textures->ceiling)
		mlx->textures->ceiling = create_new_color(info);
	else if (!ft_strcmp(tok, "F") && !mlx->textures->floor)
		mlx->textures->floor = create_new_color(info);
	else
		ft_perror(EINVAL, "Color already set");
}

void	check_texture_input(char *line, t_cub *mlx)
{
	char	*tok;

	if (line[0] == '\0')
	{
		free(line);
		return ;
	}
	tok = ft_strtok(line, " ");
	if (!ft_strcmp(tok, "C") || !ft_strcmp(tok, "F"))
		add_color(tok, ft_strtok(NULL, "\0"), mlx);
	else
		add_texture(tok, ft_strtok(NULL, "\0"), mlx);
	free(line);
}

void	modify_pass(int *pass)
{
	if (*pass == 0)
		*pass = 10;
	else if (*pass == 10)
		*pass = 20;
	else
		*pass = 0;
}

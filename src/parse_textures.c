/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:19:30 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/03/16 10:19:31 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_textures_ok(t_tex *tex)
{
	return (tex->ceiling && tex->floor && tex->north && tex->south && tex->west
		&& tex->east);
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
		mlx->textures->south = new_file_img(tmp, mlx);
	else if (!ft_strcmp(tok, "WE") && !mlx->textures->west)
		mlx->textures->west = new_file_img(tmp, mlx);
	else if (!ft_strcmp(tok, "EA") && !mlx->textures->east)
		mlx->textures->east = new_file_img(tmp, mlx);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:47:19 by anyela            #+#    #+#             */
/*   Updated: 2024/03/16 14:08:37 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "keys.h"

void	move_input(int key_pressed, t_cub *cub)
{
	if (key_pressed == DOWN_LINUX || key_pressed == DOWN_MAC
		|| key_pressed == S_LINUX || key_pressed == S_MAC)
		cub->pl->direction = DOWN;
	else if (key_pressed == UP_LINUX || key_pressed == UP_MAC
		|| key_pressed == W_LINUX || key_pressed == W_MAC)
		cub->pl->direction = UP;
	else if (key_pressed == D_LINUX || key_pressed == D_MAC)
		cub->pl->direction = RIGHT;
	else if (key_pressed == A_LINUX || key_pressed == A_MAC)
		cub->pl->direction = LEFT;
	else if (key_pressed == LEFT_LINUX || key_pressed == LEFT_MAC)
		cub->pl->rot = -1;
	else if (key_pressed == RIGHT_LINUX || key_pressed == RIGHT_MAC)
		cub->pl->rot = 1;
}

void	print_map(char **map) // debug function delete
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

int	read_keys(int key_pressed, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	move_input(key_pressed, cub);
	if (key_pressed == E_LINUX || key_pressed == E_MAC)
		cub->pl->door = 1;
	if (key_pressed == 32 || key_pressed == 49) // debug function delete 
		print_map(cub->dt->map2d);
	if (key_pressed == ESC_LINUX || key_pressed == ESC_MAC)
		exit_win();
	return (0);
}

void	hook(t_cub *mlx)
{
	if (mlx->pl->rot)
		rotate_player(mlx->pl);
	if (mlx->pl->direction != NONE)
		general_move_player(mlx);
	if (mlx->pl->door)
		cast_door_ray(mlx);
}

int	exit_win(void)
{
	exit(EXIT_SUCCESS);
}

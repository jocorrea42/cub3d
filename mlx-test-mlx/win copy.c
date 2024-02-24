/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:43:53 by jocorrea          #+#    #+#             */
/*   Updated: 2024/02/24 14:48:50 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "win.h"

t_win new_program(int w, int h, char *str)
{
	void *mlx_ptr;

	mlx_ptr = mlx_init();
	return ((t_win){mlx_ptr, mlx_new_window(mlx_ptr, w, h, str), w, h});
}

int	exit_win(t_win *window)
{
	if (window)
		mlx_destroy_window(window->mlx_ptr, window->win_ptr);
	exit(EXIT_SUCCESS);
}

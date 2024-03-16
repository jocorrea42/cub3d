/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyela <anyela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:19:51 by jocorrea          #+#    #+#             */
/*   Updated: 2024/03/03 14:39:02 by anyela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	mlx;

	if (argc != 2)
		ft_perror(EINVAL, "./so_long [MAP.cub]");
	init_structs(&mlx);
	parse_input(argv[1], &mlx);
	start_the_game(&mlx);
	return (0);
}

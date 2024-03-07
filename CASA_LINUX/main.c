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

/*
int main(void)
{
 	t_cub t;

	t.img = new_program(600, 500, "animations");
	if (!t.img.win_ptr)
		return (2);
	{
		// Put image 
		t_img	tloz_img;
		tloz_img = new_file_img("img.xpm", t.img);
		if (!tloz_img.img_ptr)
			return (1);
		mlx_put_image_to_window (tloz_img.mlx_ptr, tloz_img.win_ptr, tloz_img.img_ptr, 0, 0);	
	}
	mlx_loop(t.img.mlx_ptr);
	return (0);
}*/

int main(void)
{
	t_data *data;

	data = init_argumet(); // init the data structure
 	start_the_game(data); // start the game
	return 0;
}

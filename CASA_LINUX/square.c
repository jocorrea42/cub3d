

#include "cub3d.h"

void put_pixel_img(t_img img, int x, int y, int color)
{
	char *dst;

	if (x >= 0 && y >= 0 && x < img.w && y < img.h)
	{
		dst = img.addr + (y * img.l_len + x * (img.bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void draw_square(t_square square, t_img img)
{
	unsigned short int i;
	unsigned short int j;

	i = -1;
	while (++i < square.size && i + square.y < img.h)
	{
		j = -1;
		while (++j < square.size && j + square.x < img.w)
			put_pixel_img(img, j + square.x, i + square.y, square.color);
	}
}

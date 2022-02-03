/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_tools_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:41:26 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/22 16:41:28 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	resize_img(t_all *s, int index, int w, int h)
{
	t_img	new_img;
	t_tex	tex;
	int		i;
	int		j;
	int		color;

	tex = s->texs[index];
	new_img.ptr = mlx_new_image(s->mlx, w, h);
	new_img.addr = mlx_get_data_addr(new_img.ptr, &new_img.bpp,
		&new_img.ll, &new_img.en);
	i = 0;
	while (i < w)
	{
		j = 0;
		while (j < h)
		{
			color = my_mlx_pixel_get(&tex.img,
				(int)(i * (float)tex.w / w), (int)(j * (float)tex.h / h));
			my_mlx_pixel_put(&new_img, i, j++, color);
		}
		i++;
	}
	s->texs[index].img = new_img;
	s->texs[index].w = w;
	s->texs[index].h = h;
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int		my_mlx_pixel_get(t_img *data, int x, int y)
{
	char	*src;

	src = data->addr + (y * data->ll + x * (data->bpp / 8));
	return (*(unsigned int*)src);
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

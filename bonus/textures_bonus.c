/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:43:11 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/22 16:43:12 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	resize_scores(t_all *s, int index, int w, int h)
{
	t_img	new_img;
	t_tex	tex;
	int		i;
	int		j;
	int		color;

	tex = s->scores[index];
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
	s->scores[index].img = new_img;
	s->scores[index].w = w;
	s->scores[index].h = h;
}

void	load_scores(t_all *s)
{
	int		i;
	char	*tmp_path;

	i = 0;
	tmp_path = ft_strdup(SCORES_PATH);
	while (i < 8)
	{
		tmp_path[16] = i + 48;
		parse_xpm(s, &s->scores[i], tmp_path);
		resize_scores(s, i++, 2 * s->win.h * (1 / 10.0), s->win.h * (1 / 10.0));
	}
}

void	handle_bonus_texs(t_all *s)
{
	resize_img(s, SKY, s->win.w * 4, s->win.h * (2.0 / 3.0));
	resize_img(s, FLOOR, BLOCK, BLOCK);
	parse_xpm(s, &s->texs[DIAM], DIAMOND_PATH);
	parse_xpm(s, &s->texs[TORCH], TORCH_PATH);
	resize_img(s, TORCH, s->win.w * (1.0 / 3.0), s->win.w * (1.0 / 3.0));
	parse_xpm(s, &s->texs[WIN], WIN_PATH);
	resize_img(s, WIN, s->win.w * (2.0 / 5.0), s->win.h * (2.0 / 5.0));
	load_scores(s);
}

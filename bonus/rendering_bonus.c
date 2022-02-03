/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:43:44 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/22 16:43:46 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	render_sky(t_all *s, t_img *frame, int *heights)
{
	int i;
	int j;
	int k;
	int col;
	int row;

	i = 0;
	col = s->pl.angle * s->win.w * 4.0 / 360;
	while (i < s->win.w)
	{
		j = s->win.cntr - heights[i] * (1 - (float)(s->pl.h) / BLOCK) - 1;
		row = (s->win.h * (2.0 / 3.0) - 1) - (s->win.cntr - j);
		while (j >= 0)
		{
			k = i - col;
			k += (k < 0) ? s->win.w * 4 : 0;
			my_mlx_pixel_put(frame, i, j--,
				my_mlx_pixel_get(&s->texs[SKY].img, k, row--));
		}
		i++;
	}
}

void	render_floor(t_all *s, t_img *frame, int *hs, double ray)
{
	int i;
	int j;
	int color;

	i = 0;
	while (i < s->win.w)
	{
		ray = check_angle(ray);
		j = s->win.cntr + hs[i] * ((float)s->pl.h / BLOCK) - 1;
		while (j < s->win.h)
		{
			color = get_floor_pxl(s, j, ray);
			my_mlx_pixel_put(frame, i, j++, color);
		}
		ray -= FOV / s->win.w;
		i++;
	}
}

void	render_sprites(t_all *s, t_img *frame, int *heights)
{
	t_tmp tmp;

	calc_spr_d(s);
	del_collected(s);
	sort_sprs(s->sprs, s->map.spr);
	tmp.i = 0;
	tmp.h = heights;
	while (tmp.i < s->map.spr && s->sprs[tmp.i].h)
	{
		tmp.shade = 1.0 / s->sprs[tmp.i].d * 500;
		tmp.col = s->sprs[tmp.i].s_col - s->sprs[tmp.i].h / 2;
		tmp.tex = (s->sprs[tmp.i].t == '2') ? s->texs[SPR] : s->texs[DIAM];
		tmp.x = 0;
		if (tmp.col < 0)
		{
			tmp.x += (-tmp.col) * ((float)tmp.tex.w / s->sprs[tmp.i].h);
			tmp.col = 0;
		}
		rend_single_spr(s, frame, tmp);
		(tmp.i)++;
	}
}

void	render_walls(t_all *s, t_img *frame, int *heights)
{
	double	ray;
	int		i;
	int		*slice;
	int		j;
	int		index;

	ray = s->pl.angle + FOV / 2;
	i = -1;
	while (++i < s->win.w)
	{
		ray = check_angle(ray);
		slice = get_slice(s, ray, &heights[i]);
		j = (s->win.cntr) - heights[i] * (1 - (float)s->pl.h / BLOCK);
		index = 0;
		if (j < 0)
		{
			index += -j;
			j = 0;
		}
		while (j < (s->win.cntr + heights[i] * ((float)s->pl.h / BLOCK) - 1)
			&& j < s->win.h)
			my_mlx_pixel_put(frame, i, j++, slice[index++]);
		free(slice);
		ray -= FOV / s->win.w;
	}
}

t_img	*create_image(t_all *s, int bmp)
{
	t_img	*frame;
	int		*heights;

	frame = malloc(sizeof(t_img));
	frame->ptr = mlx_new_image(s->mlx, s->win.w, s->win.h);
	frame->addr = mlx_get_data_addr(frame->ptr,
		&frame->bpp, &frame->ll, &frame->en);
	(!bmp) ? move(s) : 0;
	heights = malloc(s->win.w * sizeof(int));
	render_walls(s, frame, heights);
	render_sky(s, frame, heights);
	render_floor(s, frame, heights, s->pl.angle + FOV / 2);
	render_sprites(s, frame, heights);
	render_torch(s, frame);
	render_score(s, frame);
	free(heights);
	return (frame);
}

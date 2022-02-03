/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:06:09 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/20 17:06:11 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_ceiling(t_all *s, t_img *frame, int *heights)
{
	int	i;
	int	j;

	i = 0;
	while (i < s->win.w)
	{
		j = 0;
		while (j < (s->win.cntr) - heights[i] * 0.5)
			my_mlx_pixel_put(frame, i, j++, s->c);
		i++;
	}
}

void	render_floor(t_all *s, t_img *frame, int *heights)
{
	int	i;
	int	j;

	i = 0;
	while (i < s->win.w)
	{
		j = s->win.h - 1;
		while (j >= (s->win.cntr) + heights[i] * 0.5)
			my_mlx_pixel_put(frame, i, j--, s->f);
		i++;
	}
}

void	render_sprites(t_all *s, t_img *frame, int *heights)
{
	t_tmp tmp;

	calc_spr_d(s);
	sort_sprs(s->sprs, s->map.spr);
	tmp.i = 0;
	tmp.h = heights;
	while (tmp.i < s->map.spr && s->sprs[tmp.i].h)
	{
		tmp.col = s->sprs[tmp.i].s_col - s->sprs[tmp.i].h / 2;
		tmp.x = 0;
		if (tmp.col < 0)
		{
			tmp.x += (-tmp.col) * ((float)s->texs[SPR].w / s->sprs[tmp.i].h);
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
		j = (s->win.cntr) - heights[i] * 0.5;
		index = 0;
		if (j < 0)
		{
			index += -j;
			j = 0;
		}
		while (j < (s->win.cntr + heights[i] * 0.5 - 1)
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
	frame->addr = mlx_get_data_addr(frame->ptr, &frame->bpp,
		&frame->ll, &frame->en);
	(!bmp) ? move(s) : 0;
	heights = malloc(s->win.w * sizeof(int));
	render_walls(s, frame, heights);
	render_ceiling(s, frame, heights);
	render_floor(s, frame, heights);
	render_sprites(s, frame, heights);
	free(heights);
	return (frame);
}

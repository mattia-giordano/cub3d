/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_sprs_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:06:25 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/20 17:06:27 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rend_single_spr(t_all *s, t_img *frame, t_tmp tmp)
{
	double	y;
	int		k;
	int		c;

	while (tmp.col < s->sprs[tmp.i].s_col + s->sprs[tmp.i].h / 2
		&& tmp.col < s->win.w)
	{
		if (tmp.h[(tmp.col)++] < s->sprs[tmp.i].h)
		{
			k = s->win.cntr - s->sprs[tmp.i].h * 0.5;
			y = (k < 0) ? (-k) * ((float)s->texs[SPR].h / s->sprs[tmp.i].h) : 0;
			k = (k < 0) ? 0 : k;
			while (k < (s->win.cntr + (s->sprs[tmp.i].h * 0.5 - 1))
				&& k < s->win.h)
			{
				c = my_mlx_pixel_get(&s->texs[SPR].img, (int)tmp.x, (int)y);
				if (c)
					my_mlx_pixel_put(frame, (tmp.col - 1), k, c);
				k++;
				y += (float)s->texs[SPR].h / s->sprs[tmp.i].h;
			}
		}
		tmp.x += (float)s->texs[SPR].w / s->sprs[tmp.i].h;
	}
}

void	sort_sprs(t_spr *sprs, int spr_count)
{
	int		i;
	short	ordered;
	t_spr	tmp;

	ordered = 1;
	i = 0;
	while (i < spr_count - 1)
	{
		if ((sprs[i].h > sprs[i + 1].h || sprs[i].h == 0) && sprs[i + 1].h != 0)
		{
			ordered = 0;
			tmp = sprs[i];
			sprs[i] = sprs[i + 1];
			sprs[i + 1] = tmp;
		}
		i++;
	}
	if (!ordered && spr_count > 2)
		sort_sprs(sprs, spr_count - 1);
}

short	spr_in_screen(t_all *s, int i)
{
	return (((s->sprs[i].s_col >= 0
			&& s->sprs[i].s_col < s->win.w) ||
		(s->sprs[i].s_col + s->sprs[i].h / 2 >= 0
			&& s->sprs[i].s_col + s->sprs[i].h / 2 < s->win.w)
		|| (s->sprs[i].s_col - s->sprs[i].h / 2 >= 0
			&& s->sprs[i].s_col - s->sprs[i].h / 2 < s->win.w))
		&& s->sprs[i].h < s->win.h * 2);
}

void	calc_spr_d(t_all *s)
{
	int		i;
	int		d_x;
	int		d_y;
	double	alfa;

	i = 0;
	while (i < s->map.spr)
	{
		s->sprs[i].h = 0;
		d_x = s->sprs[i].x - s->pl.x;
		d_y = s->pl.y - s->sprs[i].y;
		alfa = atan2(d_y, d_x) * 180 / M_PI;
		if (!(s->pl.angle >= 0 && s->pl.angle < 90 && alfa < 0))
			alfa = check_angle(alfa);
		s->sprs[i].d = hypot(d_x, d_y) * cos(RAD((alfa - s->pl.angle)));
		s->sprs[i].h = (int)(ceil(s->win.d_k / s->sprs[i].d));
		if (alfa >= 0 && alfa < 90 && s->pl.angle > 270)
			alfa = s->pl.angle + FOV / 2 - (alfa + 360);
		else
			alfa = s->pl.angle + FOV / 2 - alfa;
		s->sprs[i].s_col = alfa * s->win.w / FOV;
		if (!spr_in_screen(s, i))
			s->sprs[i].h = 0;
		i++;
	}
}

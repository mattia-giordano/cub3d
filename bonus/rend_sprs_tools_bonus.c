/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_sprs_tools_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:43:54 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/22 16:43:56 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
			k = s->win.cntr - s->sprs[tmp.i].h * (1 - (float)s->pl.h / BLOCK);
			y = (k < 0) ? (-k) * ((float)tmp.tex.h / s->sprs[tmp.i].h) : 0;
			k = (k < 0) ? 0 : k;
			while (k < (s->win.cntr + s->sprs[tmp.i].h\
				* ((float)s->pl.h / BLOCK) - 1) && k < s->win.h)
			{
				c = my_mlx_pixel_get(&tmp.tex.img, (int)tmp.x, (int)y);
				c = handle_shading(c, tmp.shade);
				if (c)
					my_mlx_pixel_put(frame, (tmp.col - 1), k, c);
				k++;
				y += (float)tmp.tex.h / s->sprs[tmp.i].h;
			}
		}
		tmp.x += (float)tmp.tex.w / s->sprs[tmp.i].h;
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

void	spr_in_screen(t_all *s, int i)
{
	if (s->sprs[i].x / (int)BLOCK == s->pl.x / (int)BLOCK
		&& s->sprs[i].y / (int)BLOCK == s->pl.y / (int)BLOCK
		&& s->sprs[i].t == '3')
		s->sprs[i].h = -1;
	else if (!(((s->sprs[i].s_col >= 0
			&& s->sprs[i].s_col < s->win.w) ||
		(s->sprs[i].s_col + s->sprs[i].h / 2 >= 0
			&& s->sprs[i].s_col + s->sprs[i].h / 2 < s->win.w)
		|| (s->sprs[i].s_col - s->sprs[i].h / 2 >= 0
			&& s->sprs[i].s_col - s->sprs[i].h / 2 < s->win.w))
		&& s->sprs[i].h < s->win.h * 2))
		s->sprs[i].h = 0;
}

void	del_collected(t_all *s)
{
	int i;

	i = 0;
	while (i < s->map.spr)
	{
		if (s->sprs[i].h == -1)
		{
			if (i != s->map.spr - 1)
				s->sprs[i] = s->sprs[s->map.spr - 1];
			(s->map.spr)--;
			(s->collected)++;
			if (s->collected == 7)
			{
				system("killall afplay");
				system("afplay -v 0.60 ./sounds/success.mpeg &");
				s->time.end = clock();
			}
			else
				system("afplay -v 0.60 ./sounds/pickup.aif &");
			break ;
		}
		i++;
	}
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
		spr_in_screen(s, i++);
	}
}

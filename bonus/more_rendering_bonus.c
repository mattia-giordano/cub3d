/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_rendering_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:41:48 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/22 16:41:50 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	render_win(t_all *s, t_img *frame)
{
	int img_x;
	int img_y;
	int color;

	img_x = 0;
	while (img_x < s->texs[WIN].w)
	{
		img_y = 0;
		while (img_y < s->texs[WIN].h)
		{
			color = my_mlx_pixel_get(&s->texs[WIN].img, img_x, img_y);
			if (color)
				my_mlx_pixel_put(frame,
					img_x + (s->win.w / 2 - s->texs[WIN].w / 2),
					img_y + s->win.h * (1.0 / 3.0), color);
			img_y++;
		}
		img_x++;
	}
}

void	render_score(t_all *s, t_img *frame)
{
	int img_x;
	int img_y;
	int color;

	img_y = 0;
	while (img_y < s->scores[s->collected].h)
	{
		img_x = 0;
		while (img_x < s->scores[s->collected].w)
		{
			color = my_mlx_pixel_get(&s->scores[s->collected].img,
				img_x, img_y);
			if (color)
				my_mlx_pixel_put(frame,
					img_x + (s->win.w - s->scores[s->collected].w - 25),
					img_y + 25, color);
			img_x++;
		}
		img_y++;
	}
}

void	render_torch(t_all *s, t_img *frame)
{
	int i;
	int	img_x;
	int	img_y;
	int color;

	i = s->win.h - 1;
	img_y = s->texs[TORCH].h - 1;
	while (img_y >= 0)
	{
		img_x = 0;
		while (img_x < s->texs[TORCH].w)
		{
			color = my_mlx_pixel_get(&s->texs[TORCH].img, img_x, img_y);
			if (color)
				my_mlx_pixel_put(frame, img_x + s->win.w / 2, i, color);
			img_x++;
		}
		img_y--;
		i--;
	}
}

int		get_floor_pxl(t_all *s, int row, double ray)
{
	double	d;
	double	plane_d;
	int		d_x;
	int		d_y;

	plane_d = (s->win.w / 2) / tan(RAD(FOV / 2));
	d = ((float)s->pl.h / (row - s->win.cntr) * plane_d)\
		/ cos(RAD((ray - s->pl.angle)));
	d_y = (int)(s->pl.y + ((-d) * sin(RAD(ray)))) % (int)BLOCK;
	d_x = (int)(s->pl.x + (d * cos(RAD(ray)))) % (int)BLOCK;
	return (handle_shading(my_mlx_pixel_get(&s->texs[FLOOR].img,
		d_x, d_y), 1.0 / d * 500));
}

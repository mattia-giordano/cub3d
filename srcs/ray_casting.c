/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:05:47 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/20 17:05:49 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_hit	*find_ver_hit(t_all *s, double ray)
{
	t_hit	*hit;
	int		d_x;
	double	d_y;

	hit = malloc(sizeof(t_hit));
	if (90.0 < ray && ray < 270.0)
		hit->x = (s->pl.x / (int)BLOCK) * BLOCK - 0.0001;
	else
		hit->x = (s->pl.x / (int)BLOCK) * BLOCK + BLOCK;
	hit->y = s->pl.y + ((float)(s->pl.x - hit->x) * tan(RAD(ray)));
	if (!is_in_map(hit->x, hit->y, s->map))
		return (hit);
	if (s->map.ptr[map_pos(hit, s)] == '1')
		return (hit);
	d_x = (90.0 < ray && ray < 270.0) ? -BLOCK : BLOCK;
	d_y = (float)(-d_x) * tan(RAD(ray));
	while (1)
	{
		hit->x += d_x;
		hit->y += d_y;
		if (!is_in_map(hit->x, hit->y, s->map))
			return (hit);
		if (s->map.ptr[map_pos(hit, s)] == '1')
			return (hit);
	}
}

t_hit	*find_hor_hit(t_all *s, double ray)
{
	t_hit	*hit;
	double	d_x;
	int		d_y;

	hit = malloc(sizeof(t_hit));
	if (0.0 < ray && ray < 180.0)
		hit->y = (s->pl.y / (int)BLOCK) * BLOCK - 0.0001;
	else
		hit->y = (s->pl.y / (int)BLOCK) * BLOCK + BLOCK;
	hit->x = s->pl.x + ((float)(s->pl.y - hit->y) / tan(RAD(ray)));
	if (!is_in_map(hit->x, hit->y, s->map))
		return (hit);
	if (s->map.ptr[map_pos(hit, s)] == '1')
		return (hit);
	d_y = (0.0 < ray && ray < 180.0) ? -BLOCK : BLOCK;
	d_x = (float)(-d_y) / tan(RAD(ray));
	while (1)
	{
		hit->x += d_x;
		hit->y += d_y;
		if (!is_in_map(hit->x, hit->y, s->map))
			return (hit);
		if (s->map.ptr[map_pos(hit, s)] == '1')
			return (hit);
	}
}

t_hit	*cast_ray(t_all *s, double ray)
{
	t_hit *hor;
	t_hit *ver;

	if (ray != 0.0 && ray != 180.0)
	{
		hor = find_hor_hit(s, ray);
		if (!is_in_map(hor->x, hor->y, s->map))
			hor->d = -1;
		else
			hor->d = fabs((float)(s->pl.y - hor->y) / sin(RAD(ray)));
		hor->v = 0;
	}
	if (ray == 90.0 || ray == 270.0)
		return (hor);
	ver = find_ver_hit(s, ray);
	if (!is_in_map(ver->x, ver->y, s->map))
	{
		free(ver);
		return (hor);
	}
	ver->d = fabs((float)(s->pl.x - ver->x) / cos(RAD(ray)));
	ver->v = 1;
	return (nearest_hit(hor, ver, ray));
}

int		*get_slice(t_all *s, double ray, int *h)
{
	t_hit	*hit;
	t_tex	tex;
	int		i;
	int		*slice;

	hit = cast_ray(s, ray);
	*h = (int)(ceil(s->win.d_k / (hit->d * cos(RAD((ray - s->pl.angle))))));
	slice = malloc(*h * sizeof(int));
	which_text(s, *hit, &tex, ray);
	i = 0;
	free(hit);
	while (i < *h)
	{
		slice[i] = my_mlx_pixel_get(&tex.img, tex.col,
			(int)(i * ((float)tex.h / *h)));
		i++;
	}
	return (slice);
}

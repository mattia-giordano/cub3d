/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:03:42 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/20 17:03:44 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate(t_all *s)
{
	if (s->keys.left_arr)
		s->pl.angle += 5;
	if (s->keys.right_arr)
		s->pl.angle -= 5;
	s->pl.angle = check_angle(s->pl.angle);
}

void	check_collision(t_all *s, int x_to, int y_to)
{
	int		b_x;
	int		b_y;
	short	near_block;

	if (x_to >= s->map.w * BLOCK || x_to < 0
		|| y_to >= s->map.h * BLOCK || y_to < 0)
		return ;
	b_x = x_to / BLOCK;
	b_y = y_to / BLOCK;
	if (ft_is_in_string(s->map.ptr[b_y * s->map.w + b_x], " 12"))
		return ;
	near_block = ft_is_in_string(s->map.ptr[(b_y - 1) * s->map.w + b_x], "12");
	if (near_block && y_to - b_y * BLOCK < HIT_RAD)
		y_to = b_y * BLOCK + HIT_RAD;
	near_block = ft_is_in_string(s->map.ptr[(b_y + 1) * s->map.w + b_x], "12");
	if (near_block && (b_y + 1) * BLOCK - y_to < HIT_RAD)
		y_to = (b_y + 1) * BLOCK - HIT_RAD;
	near_block = ft_is_in_string(s->map.ptr[b_y * s->map.w + b_x + 1], "12");
	if (near_block && (b_x + 1) * BLOCK - x_to < HIT_RAD)
		x_to = (b_x + 1) * BLOCK - HIT_RAD;
	near_block = ft_is_in_string(s->map.ptr[b_y * s->map.w + b_x - 1], "12");
	if (near_block && x_to - b_x * BLOCK < HIT_RAD)
		x_to = b_x * BLOCK + HIT_RAD;
	s->pl.x = x_to;
	s->pl.y = y_to;
}

void	move(t_all *s)
{
	double d_x;
	double d_y;
	double speed;

	d_x = 0;
	d_y = 0;
	speed = 20.0;
	(s->keys.w && !s->keys.s) ? d_x += cos(RAD(s->pl.angle)) : 0;
	(s->keys.w && !s->keys.s) ? d_y -= sin(RAD(s->pl.angle)) : 0;
	(s->keys.a && !s->keys.d) ? d_x += cos(RAD((s->pl.angle + 90))) : 0;
	(s->keys.a && !s->keys.d) ? d_y -= sin(RAD((s->pl.angle + 90))) : 0;
	(s->keys.s && !s->keys.w) ? d_x -= cos(RAD(s->pl.angle)) : 0;
	(s->keys.s && !s->keys.w) ? d_y += sin(RAD(s->pl.angle)) : 0;
	(s->keys.d && !s->keys.a) ? d_x -= cos(RAD((s->pl.angle + 90))) : 0;
	(s->keys.d && !s->keys.a) ? d_y += sin(RAD((s->pl.angle + 90))) : 0;
	speed *= (key_count(s) > 1) ? 2.0 / 3.0 : 1;
	check_collision(s, s->pl.x + d_x * speed, s->pl.y + d_y * speed);
	rotate(s);
}

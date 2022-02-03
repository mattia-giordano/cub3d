/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:42:02 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/22 16:42:03 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	crouch(t_all *s, double *speed)
{
	if (s->keys.spacebar)
	{
		if (s->pl.h != BLOCK * (1.0 / 3.0))
			system("afplay -v 0.60 ./sounds/crouch.mpeg &");
		s->pl.h = BLOCK * (1.0 / 3.0);
		*speed *= 0.5;
	}
	if (!s->keys.spacebar && s->pl.h != BLOCK * 0.5)
		s->pl.h = BLOCK * 0.5;
}

void	rotate(t_all *s)
{
	int mouse_x;
	int mouse_y;

	mlx_mouse_get_pos(s->win.ptr, &mouse_x, &mouse_y);
	if (!(0 <= mouse_x && mouse_x < s->win.w &&
		0 <= mouse_y && mouse_y < s->win.h))
	{
		mouse_x = 0;
		mouse_y = 0;
	}
	if (s->keys.left_arr || (mouse_x && mouse_x <= s->win.w * (1.0 / 3.0)))
		s->pl.angle += 5;
	if (s->keys.right_arr || (mouse_x && mouse_x >= s->win.w * (2.0 / 3.0)))
		s->pl.angle -= 5;
	s->pl.angle = check_angle(s->pl.angle);
	if (s->keys.up_arr || (mouse_y && mouse_y <= s->win.h * (1.0 / 3.0)))
		if (s->win.cntr < (s->win.h * (2.0 / 3.0)))
			s->win.cntr += 10;
	if (s->keys.down_arr || (mouse_y && mouse_y >= s->win.h * (2.0 / 3.0)))
		if (s->win.cntr > (s->win.h * (1.0 / 3.0)))
			s->win.cntr -= 10;
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
	double	d_x;
	double	d_y;
	double	speed;
	int		key_count;

	if (s->collected == 7)
		return ;
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
	crouch(s, &speed);
	key_count = s->keys.w + s->keys.a + s->keys.s + s->keys.d;
	speed *= (key_count > 1) ? 2.0 / 3.0 : 1;
	check_collision(s, s->pl.x + d_x * speed, s->pl.y + d_y * speed);
	rotate(s);
}

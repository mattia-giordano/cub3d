/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:02:36 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/20 17:02:39 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_release(int keycode, t_all *s)
{
	if (keycode == W)
		s->keys.w = 0;
	if (keycode == A)
		s->keys.a = 0;
	if (keycode == S)
		s->keys.s = 0;
	if (keycode == D)
		s->keys.d = 0;
	if (keycode == LEFT)
		s->keys.left_arr = 0;
	if (keycode == RIGHT)
		s->keys.right_arr = 0;
	return (0);
}

int		key_press(int keycode, t_all *s)
{
	if (keycode == W)
		s->keys.w = 1;
	if (keycode == A)
		s->keys.a = 1;
	if (keycode == S)
		s->keys.s = 1;
	if (keycode == D)
		s->keys.d = 1;
	if (keycode == LEFT)
		s->keys.left_arr = 1;
	if (keycode == RIGHT)
		s->keys.right_arr = 1;
	if (keycode == ESC)
		clean_all(s, 1);
	return (0);
}

void	init_keys(t_all *s, t_keys *keys)
{
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->left_arr = 0;
	keys->right_arr = 0;
	s->keys = *keys;
}

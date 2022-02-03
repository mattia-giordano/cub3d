/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:39:56 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/22 16:39:58 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		exit_hook(t_all *s)
{
	clean_all(s, 0);
	return (0);
}

void	clean_all(t_all *s, short win)
{
	int i;

	if (s->map.ptr)
		free(s->map.ptr);
	i = 0;
	while (i < 10)
		if (s->texs[i++].img.ptr)
			mlx_destroy_image(s->mlx, s->texs[i - 1].img.ptr);
	i = 0;
	if (s->sprs)
		free(s->sprs);
	if (win)
	{
		i = 0;
		while (i < 8)
			mlx_destroy_image(s->mlx, s->scores[i++].img.ptr);
		if (s->collected != 7)
			system("killall afplay");
		else
			system("echo \"\033[0;32mSuccess!!!\"");
		mlx_destroy_window(s->mlx, s->win.ptr);
	}
	exit(0);
}

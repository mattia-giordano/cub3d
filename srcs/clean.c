/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:01:56 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/20 17:01:59 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	while (i < 5)
		if (s->texs[i++].img.ptr)
			mlx_destroy_image(s->mlx, s->texs[i - 1].img.ptr);
	i = 0;
	if (s->sprs)
		free(s->sprs);
	if (win)
		mlx_destroy_window(s->mlx, s->win.ptr);
	exit(0);
}

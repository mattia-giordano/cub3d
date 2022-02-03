/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:43:30 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/22 16:43:31 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	spaceskip(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
}

double	check_angle(double angle)
{
	if (angle >= 360)
		return (angle - 360);
	if (angle < 0)
		return (angle + 360);
	return (angle);
}

short	is_in_map(int x, int y, t_map map)
{
	return (!(x < 0 || x >= map.w * BLOCK || y < 0 || y >= map.h * BLOCK));
}

int		map_pos(t_hit *hit, t_all *s)
{
	return ((int)(hit->y / BLOCK) * s->map.w + (int)(hit->x / BLOCK));
}

void	display_time(t_all *s, float time)
{
	char *s_time;
	char *safe;
	char *tmp;

	tmp = ft_itoa((int)time);
	s_time = ft_strjoin("TIME : ", tmp);
	free(tmp);
	safe = s_time;
	s_time = ft_strjoin(s_time, ".");
	free(safe);
	tmp = ft_itoa((int)((time - (int)time) * 100));
	safe = s_time;
	s_time = ft_strjoin(s_time, tmp);
	free(tmp);
	free(safe);
	safe = s_time;
	s_time = ft_strjoin(s_time, " s");
	free(safe);
	if (s->collected != 7)
		mlx_string_put(s->mlx, s->win.ptr, 10, 20, WHITE, s_time);
	else
		mlx_string_put(s->mlx, s->win.ptr, s->win.w / 2 - 42,
			s->win.h * (2.0 / 3.0) - 20, BLACK, s_time);
	free(s_time);
}

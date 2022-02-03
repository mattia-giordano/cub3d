/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:04:40 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/20 17:05:01 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_hit	*nearest_hit(t_hit *hor, t_hit *ver, double ray)
{
	if (ray == 0.0 || ray == 180.0 || hor->d == -1)
	{
		if (!(ray == 0.0 || ray == 180.0))
			free(hor);
		return (ver);
	}
	if (hor->d < ver->d)
	{
		free(ver);
		return (hor);
	}
	free(hor);
	return (ver);
}

void	which_text(t_all *s, t_hit hit, t_tex *tex, double ray)
{
	if (!hit.v)
	{
		if (0.0 < ray && ray < 180.0)
		{
			*tex = s->texs[SO];
			tex->col = ((int)hit.x % (int)BLOCK) * ((float)tex->w / BLOCK);
		}
		else
		{
			*tex = s->texs[NO];
			tex->col = (BLOCK - (int)hit.x % (int)BLOCK)\
				* ((float)tex->w / BLOCK);
		}
		return ;
	}
	if (90.0 < ray && ray < 270.0)
	{
		*tex = s->texs[EA];
		tex->col = (BLOCK - (int)hit.y % (int)BLOCK) * ((float)tex->w / BLOCK);
	}
	else
	{
		*tex = s->texs[WE];
		tex->col = ((int)hit.y % (int)BLOCK) * ((float)tex->w / BLOCK);
	}
}

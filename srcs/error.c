/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:02:22 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/20 17:02:24 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		my_strerror(int code)
{
	(code == -1) ? write(1, "Error : Couldn't open file\n", 27) : 0;
	(code == -3) ? write(1, "Error : Resolution specified twice\n", 35) : 0;
	(code == -4) ? write(1, "Error : Invalid resolution\n", 27) : 0;
	(code == -5) ? write(1, "Error : Invalid element in map\n", 31) : 0;
	(code == -6) ? write(1, "Error : Map is mising\n", 22) : 0;
	(code == -7) ? write(1, "Error : Texture path specified twice\n", 37) : 0;
	(code == -8) ? write(1, "Error : Malloc fail\n", 20) : 0;
	(code == -9) ? write(1, "Error : Invalid texture image\n", 30) : 0;
	(code == -10) ? write(1, "Error : Invalid line in file\n", 29) : 0;
	(code == -11) ? write(1, "Error : Map isn't surrounded by walls\n", 38) : 0;
	(code == -12) ? write(1, "Error : Multiple starting positions\n", 36) : 0;
	(code == -13) ? write(1, "Error : No starting position\n", 29) : 0;
	(code == -14) ? write(1, "Error : No resolution specified\n", 32) : 0;
	(code == -15) ? write(1, "Error : Missing wall/sprite texture\n", 36) : 0;
	(code == -16) ? write(1, "Error : Floor/ceiling specified twice\n", 38) : 0;
	(code == -17) ? write(1, "Error : Invalid floor/ceiling line\n", 35) : 0;
	(code == -18) ? write(1, "Error : Missing floor/sky color\n", 32) : 0;
	return (-1);
}

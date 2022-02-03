/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:02:10 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/20 17:02:13 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		render_next_frame(t_all *s)
{
	t_img	*frame;

	frame = create_image(s, 0);
	mlx_put_image_to_window(s->mlx, s->win.ptr, frame->ptr, 0, 0);
	mlx_destroy_image(s->mlx, frame->ptr);
	free(frame);
	return (0);
}

void	init_3(t_all s, char *file, short bmp)
{
	t_keys keys;

	s.mlx = mlx_init();
	if (parse_input(&s, file) == -1)
		clean_all(&s, 0);
	if (bmp == 1)
		screenshot(&s);
	init_keys(&s, &keys);
	s.win.ptr = mlx_new_window(s.mlx, s.win.w, s.win.h, "CUB3D");
	mlx_hook(s.win.ptr, 17, 0, exit_hook, &s);
	mlx_hook(s.win.ptr, 2, 1L << 0, key_press, &s);
	mlx_hook(s.win.ptr, 3, 1L << 1, key_release, &s);
	mlx_loop_hook(s.mlx, render_next_frame, &s);
	mlx_loop(s.mlx);
}

void	init_2(t_all s, char *file, short bmp)
{
	t_tex	texs[5];
	t_img	tmp;
	t_pl	pl;
	int		i;

	tmp.ptr = NULL;
	i = 0;
	while (i < 5)
	{
		texs[i].w = 0;
		texs[i].h = 0;
		texs[i++].img = tmp;
	}
	s.texs = texs;
	s.f = NO_COLOR;
	s.c = NO_COLOR;
	pl.x = 0;
	pl.y = 0;
	s.pl = pl;
	init_3(s, file, bmp);
}

void	init(char *file, short bmp)
{
	t_all	s;
	t_win	win;
	t_map	map;

	s.mlx = NULL;
	s.sprs = NULL;
	win.ptr = NULL;
	win.h = 0;
	win.w = 0;
	s.win = win;
	map.ptr = NULL;
	map.h = 0;
	map.w = 0;
	map.spr = 0;
	s.map = map;
	init_2(s, file, bmp);
}

int		main(int nargs, char *args[])
{
	if (nargs == 3 && ft_check_ext(args[1], "cub")
		&& !ft_strcmp(args[2], "--save"))
		init(args[1], 1);
	else if (nargs == 2 && ft_check_ext(args[1], "cub"))
		init(args[1], 0);
	else
		write(1, "Error : Invalid arguments\n", 26);
}

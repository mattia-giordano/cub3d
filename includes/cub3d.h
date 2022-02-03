/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:06:58 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/20 17:07:00 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

# include "libft.h"
# include "mlx.h"

# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124
# define ESC 53
# define NO	0
# define SO 1
# define WE 2
# define EA 3
# define SPR 4
# define BLOCK 192.0
# define HIT_RAD 70.0
# define FOV 66.0
# define MAX_RES_W 2560
# define MAX_RES_H 1440
# define NO_COLOR 0xFF000000

# define RAD(angle) (angle * M_PI / 180.0)

typedef struct	s_hit
{
	double		x;
	double		y;
	double		d;
	short		v;
}				t_hit;

typedef struct	s_keys
{
	short		w;
	short		a;
	short		s;
	short		d;
	short		left_arr;
	short		right_arr;
}				t_keys;

typedef struct	s_win
{
	void		*ptr;
	int			h;
	int			w;
	int			cntr;
	double		d_k;
}				t_win;

typedef struct	s_img
{
	void		*ptr;
	char		*addr;
	int			bpp;
	int			ll;
	int			en;
}				t_img;

typedef struct	s_map
{
	char		*ptr;
	int			h;
	int			w;
	int			spr;
}				t_map;

typedef struct	s_pl
{
	int			x;
	int			y;
	double		angle;
}				t_pl;

typedef struct	s_spr
{
	int			x;
	int			y;
	int			h;
	double		d;
	int			s_col;
}				t_spr;

typedef struct	s_tex
{
	int			w;
	int			h;
	int			col;
	t_img		img;
}				t_tex;

typedef struct	s_all
{
	void		*mlx;
	t_win		win;
	t_map		map;
	t_pl		pl;
	t_spr		*sprs;
	t_tex		*texs;
	int			f;
	int			c;
	t_keys		keys;
}				t_all;

typedef struct	s_tmp
{
	int			col;
	int			i;
	int			*h;
	double		x;
}				t_tmp;

int				parse_input(t_all *s, char *file);
int				parse_texture(t_all *s, int index, char *line, int *i);
int				parse_map(t_all *s, char *line, int *i, short *map);

int				mapcheck(t_all *s);
int				allsetcheck(t_all *s);

void			init_keys(t_all *s, t_keys *keys);
int				key_press(int keycode, t_all *s);
int				key_release(int keycode, t_all *s);
void			move(t_all *s);

void			find_sprs(t_all *s);
void			calc_spr_d(t_all *s);
void			sort_sprs(t_spr *sprs, int spr_count);
void			rend_single_spr(t_all *s, t_img *frame, t_tmp tmp);

int				*get_slice(t_all *s, double ray, int *height);
void			which_text(t_all *s, t_hit hit, t_tex *tex, double ray);
t_hit			*nearest_hit(t_hit *hor, t_hit *ver, double ray);
t_img			*create_image(t_all *s, int bmp);

void			clean_all(t_all *s, short win);
int				exit_hook(t_all *s);

int				create_trgb(int t, int r, int g, int b);
int				my_mlx_pixel_get(t_img *data, int x, int y);
void			my_mlx_pixel_put(t_img *data, int x, int y, int color);

void			screenshot(t_all *s);

int				my_strerror(int code);
void			spaceskip(char *str, int *i);
int				key_count(t_all *s);
double			check_angle(double angle);
int				map_pos(t_hit *hit, t_all *s);
short			is_in_map(int x, int y, t_map map);

#endif

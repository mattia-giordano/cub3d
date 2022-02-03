/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:40:26 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/22 16:40:28 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>

# include "libft.h"
# include "mlx.h"

# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124
# define UP 126
# define DOWN 125
# define SPACE 49
# define ESC 53
# define NO	0
# define SO 1
# define WE 2
# define EA 3
# define SPR 4
# define FLOOR 5
# define SKY 6
# define DIAM 7
# define TORCH 8
# define WIN 9
# define DIAMOND_PATH "./textures/diamond.xpm"
# define TORCH_PATH "./textures/torch.xpm"
# define WIN_PATH "./textures/win.xpm"
# define SCORES_PATH "./textures/score0.xpm"
# define BLOCK 192.0
# define HIT_RAD 70.0
# define FOV 66.0
# define MAX_RES_W 2560
# define MAX_RES_H 1440
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000

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
	short		up_arr;
	short		down_arr;
	short		spacebar;
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
	int			h;
}				t_pl;

typedef struct	s_spr
{
	int			x;
	int			y;
	int			h;
	double		d;
	int			s_col;
	char		t;
}				t_spr;

typedef struct	s_tex
{
	int			w;
	int			h;
	int			col;
	t_img		img;
}				t_tex;

typedef struct	s_time
{
	clock_t		start;
	clock_t		music;
	clock_t		end;
}				t_time;

typedef struct	s_all
{
	void		*mlx;
	t_win		win;
	t_map		map;
	t_pl		pl;
	t_spr		*sprs;
	t_tex		*texs;
	t_tex		*scores;
	t_keys		keys;
	int			collected;
	t_time		time;
	clock_t		start;
	clock_t		mjusic;
	clock_t		end;
}				t_all;

typedef struct	s_tmp
{
	int			col;
	int			i;
	int			*h;
	double		x;
	double		shade;
	t_tex		tex;
}				t_tmp;

int				parse_input(t_all *s, char *file);
int				parse_texture(t_all *s, int index, char *line, int *i);
int				parse_map(t_all *s, char *line, int *i, short *map);
int				parse_xpm(t_all *s, t_tex *tex_addr, char *file);

int				mapcheck(t_all *s);
int				allsetcheck(t_all *s);

void			init_keys(t_all *s, t_keys *keys);
int				key_press(int keycode, t_all *s);
int				key_release(int keycode, t_all *s);
void			move(t_all *s);

void			render_torch(t_all *s, t_img *frame);
void			render_score(t_all *s, t_img *frame);
void			render_win(t_all *s, t_img *frame);

int				exit_hook(t_all *s);
void			clean_all(t_all *s, short win);

void			my_mlx_pixel_put(t_img *data, int x, int y, int color);
int				my_mlx_pixel_get(t_img *data, int x, int y);
int				create_trgb(int t, int r, int g, int b);
void			resize_img(t_all *s, int index, int new_w, int new_h);

int				*get_slice(t_all *s, double ray, int *height);
void			which_text(t_all *s, t_hit hit, t_tex *tex, double ray);
t_hit			*nearest_hit(t_hit *hor, t_hit *ver, double ray);
t_img			*create_image(t_all *s, int bmp);

void			calc_spr_d(t_all *s);
void			sort_sprs(t_spr *sprs, int spr_count);
void			rend_single_spr(t_all *s, t_img *frame, t_tmp tmp);
void			del_collected(t_all *s);

int				handle_shading(int color, double shade);
int				get_floor_pxl(t_all *s, int row, double ray);
void			handle_bonus_texs(t_all *s);

void			screenshot(t_all *s);

void			display_time(t_all *s, float time);
int				my_strerror(int code);
void			spaceskip(char *str, int *i);
double			check_angle(double angle);
int				map_pos(t_hit *hit, t_all *s);
short			is_in_map(int x, int y, t_map map);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:05:32 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/20 17:05:34 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parse_res(t_all *s, char *line, int *i)
{
	if (s->win.w != 0 || s->win.h != 0)
		return (-3);
	(*i)++;
	s->win.w = ft_atoi(line, i);
	s->win.h = ft_atoi(line, i);
	if (s->win.w > MAX_RES_W)
		s->win.w = MAX_RES_W;
	if (s->win.h > MAX_RES_H)
		s->win.h = MAX_RES_H;
	s->win.cntr = s->win.h / 2;
	s->win.d_k = BLOCK * (s->win.w / 2) / tan(RAD(FOV / 2));
	spaceskip(line, i);
	if (s->win.w <= 0 || s->win.h <= 0 || line[*i] != '\0')
		return (-4);
	return (0);
}

int		parse_cardinals(t_all *s, char *line, int *i)
{
	if (line[*i] == 'N' && line[*i + 1] == 'O' && line[*i + 2] == ' ')
		return (parse_texture(s, NO, line, i));
	else if (line[*i] == 'S' && line[*i + 1] == 'O' && line[*i + 2] == ' ')
		return (parse_texture(s, SO, line, i));
	else if (line[*i] == 'W' && line[*i + 1] == 'E' && line[*i + 2] == ' ')
		return (parse_texture(s, WE, line, i));
	else if (line[*i] == 'E' && line[*i + 1] == 'A' && line[*i + 2] == ' ')
		return (parse_texture(s, EA, line, i));
	return (0);
}

int		parse_color(int *color, char *line, int *i)
{
	int r;
	int g;
	int b;

	if ((unsigned int)(*color) != NO_COLOR)
		return (-16);
	(*i)++;
	r = (line[*i]) ? ft_atoi(line, i) : -1;
	spaceskip(line, i);
	(line[*i] && line[*i] == ',') ? (*i)++ : 0;
	g = (line[*i]) ? ft_atoi(line, i) : -1;
	spaceskip(line, i);
	(line[*i] && line[*i] == ',') ? (*i)++ : 0;
	b = (line[*i]) ? ft_atoi(line, i) : -1;
	spaceskip(line, i);
	if (line[*i] != '\0' || r > 255 || r < 0 ||
		g > 255 || g < 0 || b > 255 || b < 0)
		return (-17);
	*color = create_trgb(0, r, g, b);
	return (0);
}

int		handle_line(t_all *s, char *line, short *map)
{
	int	i;
	int err;

	i = 0;
	err = 0;
	spaceskip(line, &i);
	if (line[i] == '1' || *map == 1)
		err = parse_map(s, line, &i, map);
	else if (line[i] == 'R' && line[i + 1] == ' ')
		err = parse_res(s, line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		err = parse_color(&s->f, line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		err = parse_color(&s->c, line, &i);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		err = parse_texture(s, SPR, line, &i);
	else if (ft_is_in_string(line[i], "NSEW"))
		err = parse_cardinals(s, line, &i);
	if (err == 0 && line[i] != '\0')
		return (my_strerror(-10));
	return (err < 0 ? my_strerror(err) : 0);
}

int		parse_input(t_all *s, char *file)
{
	char	*line;
	int		fd;
	int		ret;
	short	map;

	line = NULL;
	map = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (my_strerror(-1));
	while ((ret = ft_gnl(fd, &line)) > 0)
	{
		if ((ret = handle_line(s, line, &map)) < 0)
			break ;
		free(line);
	}
	free(line);
	close(fd);
	if (ret < 0)
		return (-1);
	if (mapcheck(s) < 0)
		return (-1);
	if (s->map.spr)
		find_sprs(s);
	return (allsetcheck(s));
}

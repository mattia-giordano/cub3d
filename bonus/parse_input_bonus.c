/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:42:14 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/22 16:42:15 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	find_sprs(t_all *s)
{
	int i;
	int j;
	int index;

	s->sprs = malloc(s->map.spr * sizeof(t_spr));
	i = 0;
	index = 0;
	while (i < s->map.h && index < s->map.spr)
	{
		j = 0;
		while (j < s->map.w && index < s->map.spr)
		{
			if (ft_is_in_string(s->map.ptr[i * s->map.w + j], "23"))
			{
				s->sprs[index].x = j * BLOCK + BLOCK / 2;
				s->sprs[index].y = i * BLOCK + BLOCK / 2;
				s->sprs[index++].t = s->map.ptr[i * s->map.w + j];
			}
			j++;
		}
		i++;
	}
}

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
		err = parse_texture(s, FLOOR, line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		err = parse_texture(s, SKY, line, &i);
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

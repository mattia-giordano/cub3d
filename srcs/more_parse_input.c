/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_parse_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:03:28 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/20 17:03:33 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		allsetcheck(t_all *s)
{
	if (s->win.w <= 0 || s->win.h <= 0)
		return (my_strerror(-14));
	if (s->texs[NO].img.ptr == NULL || s->texs[SO].img.ptr == NULL
		|| s->texs[WE].img.ptr == NULL || s->texs[EA].img.ptr == NULL
		|| s->texs[SPR].img.ptr == NULL)
		return (my_strerror(-15));
	if ((unsigned int)(s->f) == NO_COLOR || (unsigned int)(s->c) == NO_COLOR)
		return (my_strerror(-18));
	return (0);
}

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
			if (s->map.ptr[i * s->map.w + j] == '2')
			{
				s->sprs[index].x = j * BLOCK + BLOCK / 2;
				s->sprs[index++].y = i * BLOCK + BLOCK / 2;
			}
			j++;
		}
		i++;
	}
}

int		parse_xpm(t_all *s, t_tex *tex_addr, char *file)
{
	int fd;

	if (!ft_check_ext(file, "xpm"))
		return (-1);
	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	close(fd);
	tex_addr->img.ptr = mlx_xpm_file_to_image(s->mlx,\
		file, &tex_addr->w, &tex_addr->h);
	tex_addr->img.addr = mlx_get_data_addr(tex_addr->img.ptr,\
		&tex_addr->img.bpp, &tex_addr->img.ll, &tex_addr->img.en);
	return (0);
}

int		parse_texture(t_all *s, int index, char *line, int *i)
{
	int		j;
	char	*file;
	t_tex	*tex_addr;

	tex_addr = &s->texs[index];
	if (tex_addr->img.ptr != NULL)
		return (-7);
	(*i) += 2;
	spaceskip(line, i);
	j = *i;
	while (line[*i] != ' ' && line[*i])
		(*i)++;
	if (!(file = malloc(*i - j + 1)))
		return (-8);
	*i = j;
	j = 0;
	while (line[*i] != ' ' && line[*i])
		file[j++] = line[(*i)++];
	file[j] = 0;
	j = parse_xpm(s, tex_addr, file);
	free(file);
	return ((j < 0) ? -9 : 0);
}

int		parse_map(t_all *s, char *line, int *i, short *map)
{
	int		j;
	char	*tmp;
	char	*safe;

	j = 0;
	while (line[j])
		if (!ft_is_in_string(line[j++], " 012NSWE"))
			return (-5);
	*i = j;
	*map = 1;
	if (!s->map.ptr)
		s->map.ptr = ft_strdup("");
	safe = s->map.ptr;
	tmp = ft_strjoin(line, "\n");
	s->map.ptr = ft_strjoin(s->map.ptr, tmp);
	free(safe);
	free(tmp);
	return (0);
}

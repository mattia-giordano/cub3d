/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_parse_input_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:41:38 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/22 16:41:39 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	allsetcheck(t_all *s)
{
	if (s->win.w <= 0 || s->win.h <= 0)
		return (my_strerror(-14));
	if (s->texs[NO].img.ptr == NULL || s->texs[SO].img.ptr == NULL
		|| s->texs[WE].img.ptr == NULL || s->texs[EA].img.ptr == NULL
		|| s->texs[SPR].img.ptr == NULL)
		return (my_strerror(-15));
	if (s->texs[FLOOR].img.ptr == NULL || s->texs[SKY].img.ptr == NULL)
		return (my_strerror(-16));
	return (0);
}

int	parse_xpm(t_all *s, t_tex *tex_addr, char *file)
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

int	parse_texture(t_all *s, int index, char *line, int *i)
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

int	parse_map(t_all *s, char *line, int *i, short *map)
{
	int		j;
	char	*tmp;
	char	*safe;

	j = 0;
	while (line[j])
		if (!ft_is_in_string(line[j++], " 0123NSWE"))
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

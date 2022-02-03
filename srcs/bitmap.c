/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:01:45 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/20 17:01:48 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bitmap_data(t_all *s, int fd, t_img *frame)
{
	int				i;
	int				j;
	int				color;
	unsigned char	buffer[4];

	i = s->win.h - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < s->win.w)
		{
			color = my_mlx_pixel_get(frame, j, i);
			buffer[0] = (unsigned char)(color & 0xFF);
			buffer[1] = (unsigned char)((color >> 8) & 0xFF);
			buffer[2] = (unsigned char)((color >> 16) & 0xFF);
			buffer[3] = (unsigned char)(0);
			write(fd, buffer, 4);
			j++;
		}
		i--;
	}
}

void	bitmap_image(t_all *s, int fd)
{
	int				n;
	unsigned char	header[40];

	n = 0;
	while (n < 40)
		header[n++] = (unsigned char)(0);
	header[0] = (unsigned char)(40);
	n = s->win.w;
	header[4] = (unsigned char)(n & 0xFF);
	header[5] = (unsigned char)((n >> 8) & 0xFF);
	header[6] = (unsigned char)((n >> 16) & 0xFF);
	header[7] = (unsigned char)((n >> 24) & 0xFF);
	n = s->win.h;
	header[8] = (unsigned char)(n & 0xFF);
	header[9] = (unsigned char)((n >> 8) & 0xFF);
	header[10] = (unsigned char)((n >> 16) & 0xFF);
	header[11] = (unsigned char)((n >> 24) & 0xFF);
	header[12] = (unsigned char)(1);
	header[14] = (unsigned char)(32);
	write(fd, header, 40);
}

void	bitmap_file(t_all *s, int fd)
{
	int				n;
	unsigned char	header[14];

	n = 0;
	while (n < 14)
		header[n++] = (unsigned char)(0);
	header[0] = (unsigned char)(66);
	header[1] = (unsigned char)(77);
	n = s->win.w * s->win.h * 4 + 54;
	header[2] = (unsigned char)(n & 0xFF);
	header[3] = (unsigned char)((n >> 8) & 0xFF);
	header[4] = (unsigned char)((n >> 16) & 0xFF);
	header[5] = (unsigned char)((n >> 24) & 0xFF);
	header[10] = (unsigned char)(54);
	write(fd, header, 14);
}

void	screenshot(t_all *s)
{
	int		fd;
	t_img	*frame;

	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	bitmap_file(s, fd);
	bitmap_image(s, fd);
	frame = create_image(s, 1);
	bitmap_data(s, fd, frame);
	close(fd);
	clean_all(s, 0);
}

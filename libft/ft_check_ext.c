/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:41:46 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/17 12:42:10 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

short		ft_check_ext(char *file_path, char *ext)
{
	if (ft_strlen(file_path) < (ft_strlen(ext) + 2))
		return (0);
	file_path += ft_strlen(file_path) - ft_strlen(ext);
	if (*(file_path - 1) != '.')
		return (0);
	return (!ft_strcmp(file_path, ext));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:18:30 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/17 17:18:35 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *str)
{
	int		i;
	char	*rslt;

	i = 0;
	rslt = malloc(ft_strlen(str) + 1);
	while (*str)
		rslt[i++] = *str++;
	rslt[i] = 0;
	return (rslt);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:18:56 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/17 17:18:59 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *str1, char *str2)
{
	char	*rslt;
	int		i;

	rslt = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	i = 0;
	while (*str1)
		rslt[i++] = *str1++;
	while (*str2)
		rslt[i++] = *str2++;
	rslt[i] = 0;
	return (rslt);
}

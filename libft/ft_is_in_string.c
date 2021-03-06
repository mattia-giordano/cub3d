/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_in_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:55:48 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/17 18:55:59 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

short	ft_is_in_string(char c, char *str)
{
	while (*str)
	{
		if (*str++ == c)
			return (1);
	}
	return (0);
}

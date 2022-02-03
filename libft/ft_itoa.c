/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:39:31 by mgiordan          #+#    #+#             */
/*   Updated: 2021/01/13 11:39:34 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		abs(int n)
{
	return ((n < 0) ? -n : n);
}

int		calc_digits(int n)
{
	int count;

	if (n == 0)
		return (1);
	count = 0;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	short	negative;
	int		digit_count;
	int		i;
	char	*converted;

	negative = (n < 0) ? 1 : 0;
	digit_count = (negative) ? calc_digits(n) + 2 : calc_digits(n) + 1;
	if (NULL == (converted = malloc(digit_count)))
		return (NULL);
	converted[digit_count - 1] = 0;
	if (n == 0)
	{
		converted[digit_count - 2] = '0';
		return (converted);
	}
	i = digit_count - 2;
	while (n != 0)
	{
		converted[i--] = abs(n % 10) + 48;
		n /= 10;
	}
	if (negative)
		converted[i] = '-';
	return (converted);
}

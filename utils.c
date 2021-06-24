/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:48:11 by esivre            #+#    #+#             */
/*   Updated: 2021/06/24 14:30:42 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	is_char_str(char a, const char *str)
{
	while (*str)
		if (a == *str++)
			return (a);
	return (0);
}

int	ft_size_nb(unsigned long long nb, int size_base)
{
	int		len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / size_base;
		len++;
	}
	return (len);
}

int	ft_min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

int	ft_sign(intmax_t i)
{
	if (i < 0)
		return (0);
	return (1);
}

int	mult_heaviside(int i)
{
	if (i < 0)
		return (0);
	return (i);
}

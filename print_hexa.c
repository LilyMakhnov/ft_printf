/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:56:51 by esivre            #+#    #+#             */
/*   Updated: 2021/06/22 04:37:32 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_hexa(unsigned long i, char c)
{	
	char	*hexa;

	if (c == 'X')
		hexa = "0123456789ABCDEF";
	else
		hexa = "0123456789abcdef";
	while (i > 15)
	{
		ft_putnbr_hexa(i / 16, c);
		i %= 16;
	}
	ft_putchar_fd(hexa[i], 1);
}

int	prepend_hexa(char a)
{
	ft_putchar_fd('0', 1);
	ft_putchar_fd(a, 1);
	return (2);
}

int	dirac(int i)
{
	if (!i)
		return (1);
	return (0);
}

int	ft_case_hexa(va_list arg, t_flags flags)
{
	unsigned long long	i;
	int				wc;
	int				fill;
	int				nbzero;

//	i = va_arg(arg, unsigned int);
	i = convert(arg, flags, 0);
	wc = ft_size_nb(i, 16);
	nbzero = ft_max(wc, flags.precision) - wc;
	fill = ft_max(flags.fieldwidth - ft_max(wc
				+ 2 * flags.hashtag * (1 - dirac(i)), flags.precision), 0);
	wc += exception(i, &fill, &nbzero, flags);
	if (!flags.minus)
		while (fill--)
			ft_putchar_fd(' ', 1);
	if (flags.hashtag == 1 && i)
		wc += prepend_hexa(flags.convertspec);
	while (nbzero--)
		ft_putchar_fd('0', 1);
	if (!(!i && !flags.precision))
		ft_putnbr_hexa(i, flags.convertspec);
	else
		wc--;
	while (fill-- && flags.minus)
		ft_putchar_fd(' ', 1);
	return (wc);
}

int	ft_case_pointer(va_list arg, t_flags flags)
{
	long long	i;
	int			wc;
	int			fill;
	int			nbzero;

	i = (unsigned long long)va_arg(arg, unsigned long long);
	wc = ft_size_nb(i, 16);
	nbzero = ft_max(wc, flags.precision) - wc;
	fill = ft_max(flags.fieldwidth - ft_max(wc, flags.precision) - 2, 0);
	wc += nbzero + fill;
	if (!flags.minus)
		while (fill--)
			ft_putchar_fd(' ', 1);
	wc += prepend_hexa('x');
	while (nbzero--)
		ft_putchar_fd('0', 1);
	ft_putnbr_hexa(i, 'x');
	while (fill-- && flags.minus)
		ft_putchar_fd(' ', 1);
	return (wc);
}

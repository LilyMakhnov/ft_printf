/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_deci.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:57:26 by esivre            #+#    #+#             */
/*   Updated: 2021/06/24 14:39:47 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(unsigned long i)
{
	while (i > 9)
	{
		ft_putnbr(i / 10);
		i %= 10;
	}
	ft_putchar_fd('0' + i, 1);
}

int	ft_putsign(t_flags flags, int sign)
{
	if (!sign)
	{
		ft_putchar_fd('-', 1);
		return (1);
	}
	return (0);
}

long	convert(va_list arg, t_flags flags, char sgd)
{
	intmax_t	i;

	if (flags.h == 1 && sgd)
		i = (short)va_arg(arg, int);
	else if (flags.h == 1 && !sgd)
		i = (unsigned short)va_arg(arg, int);
	else if (flags.h == 2 && sgd)
		i = (char)va_arg(arg, int);
	else if (flags.h == 2 && !sgd)
		i = (unsigned char)va_arg(arg, int);
	else if (flags.l == 1 && sgd)
		i = (long)va_arg(arg, long);
	else if (flags.l == 1 && !sgd)
		i = (unsigned long)va_arg(arg, unsigned long);
	else if (flags.l == 2 && sgd)
		i = (long long)va_arg(arg, long long);
	else if (flags.l == 2 && !sgd)
		i = (unsigned long long)va_arg(arg, unsigned long long);
	else if (!sgd)
		i = (unsigned int)va_arg(arg, int);
	else
		i = va_arg(arg, int);
	return (i);
}

int	ft_case_int(va_list arg, t_flags flags)
{
	intmax_t	i;
	int			wc;
	int			fill;
	int			nbzero;

	i = convert(arg, flags, 1);
	wc = ft_size_nb(i * (-1) * (1 - ft_sign(i)) + i * ft_sign(i), 10);
	nbzero = mult_heaviside(flags.precision - wc);
	fill = mult_heaviside(flags.fieldwidth - wc - nbzero - (1 - ft_sign(i)));
	wc += exception(i, &fill, &nbzero, &flags);
	if (!flags.minus)
		while (fill--)
			ft_putchar_fd(' ', 1);
	wc += ft_putsign(flags, ft_sign(i));
	while (nbzero--)
		ft_putchar_fd('0', 1);
	if (!(!i && !flags.precision))
		ft_putnbr(i * (-1) * (1 - ft_sign(i)) + i * ft_sign(i));
	else
		wc--;
	while (fill-- && flags.minus)
		ft_putchar_fd(' ', 1);
	return (wc);
}

int	ft_case_unsint(va_list arg, t_flags flags)
{
	unsigned long long	i;
	int					wc;
	int					fill;
	int					nbzero;

	i = convert(arg, flags, 0);
	wc = ft_size_nb(i, 10);
	nbzero = mult_heaviside(flags.precision - wc);
	fill = mult_heaviside(flags.fieldwidth - wc - nbzero);
	wc += exception(i, &fill, &nbzero, &flags);
	if (!flags.minus)
		while (fill--)
			ft_putchar_fd(' ', 1);
	while (nbzero--)
		ft_putchar_fd('0', 1);
	if (!(!i && !flags.precision))
		ft_putnbr(i);
	else
		wc--;
	while (fill-- && flags.minus)
		ft_putchar_fd(' ', 1);
	return (wc);
}

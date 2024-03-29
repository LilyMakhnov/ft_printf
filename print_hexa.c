/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:56:51 by esivre            #+#    #+#             */
/*   Updated: 2021/06/24 14:28:52 by esivre           ###   ########.fr       */
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

int	ft_case_hexa(va_list arg, t_flags flags)
{
	unsigned long long	i;
	int					wc;
	int					fill;
	int					nbzero;

	i = convert(arg, flags, 0);
	wc = ft_size_nb(i, 16);
	nbzero = mult_heaviside(flags.precision - wc);
	fill = mult_heaviside(flags.fieldwidth - wc - nbzero);
	wc += exception(i, &fill, &nbzero, &flags);
	if (!flags.minus)
		while (fill--)
			ft_putchar_fd(' ', 1);
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
	nbzero = mult_heaviside(flags.precision - wc);
	fill = mult_heaviside(flags.fieldwidth - wc - nbzero - 2);
	if (!i && !flags.precision && flags.fieldwidth > 2)
		fill++;
	wc += nbzero + fill;
	if (!flags.minus)
		while (fill--)
			ft_putchar_fd(' ', 1);
	wc += prepend_hexa('x');
	while (nbzero-- && !i)
		ft_putchar_fd('0', 1);
	if (!(!i && !flags.precision))
		ft_putnbr_hexa(i, 'x');
	else
		wc--;
	while (fill-- && flags.minus)
		ft_putchar_fd(' ', 1);
	return (wc);
}

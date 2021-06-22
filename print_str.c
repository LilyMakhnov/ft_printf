/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:46:43 by esivre            #+#    #+#             */
/*   Updated: 2021/06/22 00:15:50 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr_precision(char *str, unsigned int pre)
{
	while (*str && pre--)
		write(1, str++, 1);
}

void	print_str(char *str, unsigned int fill, t_flags flags)
{
	if (!flags.minus)
		while (fill--)
			ft_putchar_fd(flags.zero, 1);
	ft_putstr_precision(str, flags.precision);
	while (fill-- && flags.minus)
		ft_putchar_fd(' ', 1);
}

int	printf_str(va_list arg, t_flags flags)
{
	int		fill;
	int		nbrchar;
	char	*str;

	str = (char *)va_arg(arg, char *);
	if (!str)
		str = "(null)";
	if (flags.precision < 0)
		flags.precision = ft_strlen(str);
	if (flags.fieldwidth < 0)
		flags.fieldwidth = ft_strlen(str);
	nbrchar = ft_min(flags.precision, (int)ft_strlen(str));
	fill = ft_max(flags.fieldwidth - nbrchar, 0);
	print_str(str, fill, flags);
	return (nbrchar + fill);
}

int	printf_char(va_list arg, t_flags flags)
{
	unsigned int	fill;
	int				wc;
	char			c;

	c = (char)va_arg(arg, int);
	if (flags.fieldwidth > 1)
		fill = flags.fieldwidth - 1;
	else
		fill = 0;
	wc = (int)fill;
	if (!flags.minus)
		while (fill--)
			ft_putchar_fd(flags.zero, 1);
	ft_putchar_fd(c, 1);
	while (fill-- && flags.minus)
		ft_putchar_fd(' ', 1);
	return (1 + wc);
}

int	printf_percent(t_flags flags)
{
	unsigned int	fill;
	int				wc;

	if (flags.fieldwidth > 1)
		fill = flags.fieldwidth - 1;
	else
		fill = 0;
	wc = (int)fill;
	if (!flags.minus)
		while (fill--)
			ft_putchar_fd(flags.zero, 1);
	ft_putchar_fd('%', 1);
	while (fill-- && flags.minus)
		ft_putchar_fd(' ', 1);
	return (1 + wc);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:34:40 by esivre            #+#    #+#             */
/*   Updated: 2021/06/24 14:26:24 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	exception(int i, int *fill, int *nbzero, t_flags *flags)
{
	if (flags->precision == 0 && flags->fieldwidth != 0 && i == 0)
		(*fill)++;
	if (flags->zero == '0' && !flags->minus && flags->precision < 0)
	{
		(*nbzero) += *fill;
		*fill = 0;
	}
	return (*fill + *nbzero);
}

int	ft_conv(va_list arg, t_flags flags)
{
	int	written_char;

	written_char = 0;
	if (flags.convertspec == 'c')
		written_char += printf_char(arg, flags);
	else if (flags.convertspec == 's')
		written_char += printf_str(arg, flags);
	else if (flags.convertspec == 'p')
		written_char += ft_case_pointer(arg, flags);
	else if (flags.convertspec == 'i' || flags.convertspec == 'd')
		written_char += ft_case_int(arg, flags);
	else if (flags.convertspec == 'u')
		written_char += ft_case_unsint(arg, flags);
	else if (flags.convertspec == 'x' || flags.convertspec == 'X')
		written_char += ft_case_hexa(arg, flags);
	else if (flags.convertspec == '%')
		written_char += printf_percent(flags);
	return (written_char);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	size_t	written_char;
	t_flags	flags;

	va_start(arg, format);
	written_char = 0;
	while (*format)
	{
		if (*format != '%')
		{
			ft_putchar_fd(*format++, 1);
			written_char++;
		}
		else
		{
			format++;
			init_t_flags(&flags);
			add_flags(&format, &flags, arg);
			written_char += ft_conv(arg, flags);
		}
	}
	va_end(arg);
	return (written_char);
}

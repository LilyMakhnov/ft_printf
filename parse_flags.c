/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 12:34:24 by esivre            #+#    #+#             */
/*   Updated: 2021/06/23 14:43:05 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_t_flags(t_flags *flags)
{
	flags->precision = -1;
	flags->fieldwidth = 0;
	flags->minus = 0;
	flags->zero = ' ';
	flags->convertspec = 0;
	flags->hashtag = 0;
	flags->plus = 0;
	flags->space = 0;
	flags->h = 0;
	flags->l = 0;
}

void	set_precision(const char **format, t_flags *flags, va_list arg)
{
	flags->precision = 0;
	(*format)++;
	if (**format == '*')
	{
		flags->precision = (int)va_arg(arg, int);
		(*format)++;
	}
	else
		while (ft_isdigit(**format))
			flags->precision = 10 * flags->precision + *((*format)++) - '0';
}

void	set_fieldwidth(const char **format, t_flags *flags, va_list arg)
{
	flags->fieldwidth = 0;
	if (**format == '*')
	{
		flags->fieldwidth = (int)va_arg(arg, int);
		if (flags->fieldwidth < 0)
		{
			flags->minus = 1;
			flags->fieldwidth *= -1;
		}
		(*format)++;
	}
	else
		while (ft_isdigit(**format))
			flags->fieldwidth = 10 * flags->fieldwidth + *((*format)++) - '0';
}

char	ft_convertspec(const char **format)
{
	char	a;

	a = **format;
	if (is_char_str(a, "cspdiuxXf%"))
	{
		(*format)++;
		return (a);
	}
	return (0);
}

void	add_flags(const char **format, t_flags *flags, va_list arg)
{
	while (**format && (**format == '0' || **format == '-'
				|| **format == '#' || **format == '+'
				|| **format == ' '))
	{
		if (**format == '0')
			flags->zero = '0';
		if (**format == '-')
			flags->minus = 1;
		if (**format == '#')
			flags->hashtag = 1;
		if (**format == '+')
			flags->plus = 1;
		if (**format == ' ')
			flags->space = 1;
		(*format)++;
	}
	if (ft_isdigit(**format) || **format == '*')
		set_fieldwidth(format, flags, arg);
	if (**format == '.')
		set_precision(format, flags, arg);
	while (**format == 'h' || **format == 'l')
	{
		if (**format == 'h')
			flags->h += 1;
		if (**format == 'l')
			flags->l += 1;
		(*format)++;
	}
	flags->convertspec = ft_convertspec(format);
}

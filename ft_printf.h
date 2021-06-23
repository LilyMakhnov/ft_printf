/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 12:31:43 by esivre            #+#    #+#             */
/*   Updated: 2021/06/23 13:32:59 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include "libft/libft.h"
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s__flags
{
	int precision;
	int fieldwidth;
	char zero;
	char minus;
	char convertspec;
	char hashtag;
	char plus;
	char space;
	char h;
	char l;
}		t_flags;

char	is_char_str(char a, const char *str);
void	init_t_flags(t_flags *flags);
void	set_precision(const char **format, t_flags *flags, va_list arg);
void	set_fieldwidth(const char **format, t_flags *flags, va_list arg);
char	ft_convertspec(const char **format);
void	add_flags(const char **format, t_flags *flags, va_list arg);

void	ft_putstr_precision(char *str, unsigned int pre);
void	print_str(char *str, unsigned int fill, t_flags flags);
int		printf_str(va_list arg, t_flags flags);
int		printf_char(va_list arg, t_flags flags);
int		printf_percent(t_flags flags);

int 	ft_max(int a, int b);
int		ft_min(int a, int b);

char	is_char_str(char a, const char *str);
void	ft_putnbr(unsigned long i);
void	ft_putnbr_hexa(unsigned long i, char c);
int		ft_size_nb(unsigned long long nb, int size_base);
int	exception(int i, int *fill, int *nbzero, t_flags flags);

int		ft_max(int a, int b);
int		ft_min(int a, int b);
int		ft_sign(long i);
int		ft_case_int(va_list arg, t_flags flags);
int		ft_case_hexa(va_list arg, t_flags flags);
int		ft_case_pointer(va_list arg, t_flags flags);
int		ft_case_unsint(va_list arg, t_flags flags);
int		ft_conv(va_list arg, t_flags flags);
int		prepend_hexa(char a);
int		ft_printf(const char * format, ...);
int		dirac(int a);
int		ft_case_float(va_list arg, t_flags flags);
long		convert(va_list arg, t_flags flags, char sgd);


#endif

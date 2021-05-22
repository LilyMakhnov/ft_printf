#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"


typedef struct	s__flags
{
	int dot;

}		t_flags;

int	ft_putstr(const char *str)
{
	ft_putstr_fd((char*)str, 1);
	return (ft_strlen(str));
}

int	ft_putchar(const char a)
{
	ft_putchar_fd((char)a, 1);
	return (1);
}

char	is_char_str(char a, const char *str)
{
	while (*str)
		if (a == *str++)
			return (a);
	return (0);
}

int	ft_case_str(va_list arg, t_flags flag)
{
	char	*str;
	int	ret;

	str = ft_strdup((char*)va_arg(arg, char*));
	if (flag.dot >= 0  && flag.dot < (int)ft_strlen(str))
		str[flag.dot] = 0;
	ret = ft_putstr(str);
	free(str);
	return (ret);
}

int	ft_case_char(va_list arg)
{
	char a;

	a = (char)va_arg(arg, int);
	return (ft_putchar(a));
}
int	ft_putnbr(long long i)
{
	unsigned long long	n;
	int		size;

	size = 0;
	if (i < 0)
	{
		size += ft_putchar('-');
		n = -i;
	}
	else
		n = i;
	while(n > 9)
	{
		size += ft_putnbr(n / 10);
		n %= 10;
	}
	size += ft_putchar('0' + n);
	return (size);
}

int	ft_putnbr_hexa(unsigned long i, char c)
{	
	char *hexa;
	int size;

	size = 0;
	if (c == 'X')
		hexa = "0123456789ABCDEF";
	else 
		hexa = "0123456789abcdef";
	while (i > 15)
	{
		size += ft_putnbr_hexa(i / 16, c);
		i %= 16;	
	}
	size += ft_putchar(hexa[i]);
	return (size);
}

int ft_case_int(va_list arg)
{
	int i;

	i = va_arg(arg, int);
	return(ft_putnbr(i));
}

int	ft_case_hexa(va_list arg, char a)
{
	unsigned int i;

	i = va_arg(arg, unsigned int);
	return (ft_putnbr_hexa(i, a));
}

int	ft_case_pointer(va_list arg)
{
	unsigned long i;

	i = va_arg(arg, unsigned long);
	ft_putstr("0x");
	return (ft_putnbr_hexa(i, 'x') + 2);
}

int	ft_case_unsint(va_list arg)
{
	unsigned int i;

	i = (unsigned int)va_arg(arg, unsigned int);
	return (ft_putnbr(i));
}

int ft_conv(char a, va_list arg, t_flags flags)//, t_flags flag)
{
	int written_char;

	written_char = 0;
	if (a == 'c')
		written_char += ft_case_char(arg);
	if (a == 's')
		written_char += ft_case_str(arg, flags);
	if (a == 'p')
		written_char += ft_case_pointer(arg);
	if (a == 'i' || a == 'd')
		written_char += ft_case_int(arg);
	if (a == 'u')
		written_char += ft_case_unsint(arg);	
	if (a == 'x' || a == 'X')
		written_char += ft_case_hexa(arg, a);	
	if (a == '%')
		written_char += ft_putchar('%');
	return (written_char);
}

void init_t_flags(t_flags *flags)
{	
	flags->dot = -1;
}

int	add_flag(const char *format, t_flags *flag)
{
	int nbflags;
	int digit;

	digit = 0;
	nbflags = 0;
	if (is_char_str('.', format++))
	{
		nbflags = 1;
		while (ft_isdigit(*++format))
		{
			digit = 10 * digit + *format - '0';
			nbflags++;
		}
		flag->dot = digit;
	}
	return (nbflags);
}

int ft_printf(const char * format, ...)
{
	va_list arg;
	size_t written_char;
	t_flags flags;

//	str_flags = "-0.*";
	va_start(arg, format);
	written_char = 0;
	while (*format)
	{
		if (*format != '%')
			written_char += ft_putchar(*format++);
		else 
		{
			init_t_flags(&flags);
			format += add_flag(format, &flags);
			written_char += ft_conv(*++format, arg, flags);//, flag);
			format++;
		}
	}
	va_end(arg);
	return (written_char);	
}

int main(void) 
{
    	int i;
	int j;

//	i = ft_printf("str: %s, %%, int %i, char %c, p %u \n",t_flags; "Middle", 127656, 'A', -100);
//	j =    printf("str: %s, %%, int %i, char %c, p %u \n", "Middle", 127656, 'A', -100);
	i = ft_printf("str: %.7i mdr\n", 876487);
	j =    printf("str: %.*d mdr\n", 8, 876487);

	printf("size ft_printf: %d, print_f : %d\n", i, j);
	return (0);
}

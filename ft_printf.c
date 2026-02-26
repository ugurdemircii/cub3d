/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakkoc <eakkoc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:27:01 by udemirci          #+#    #+#             */
/*   Updated: 2026/02/26 21:02:34 by eakkoc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdarg.h>

static int	ft_putchar(char c)
{
	write(2, &c, 1);
	return (1);
}

static int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		return (write(1, "(null)", 6));
	}
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

static int	ft_putnbr(int n)
{
	long	num;
	int		i;

	i = 0;
	num = n;
	if (num < 0)
	{
		i += ft_putchar('-');
		num *= -1;
	}
	if (num < 10)
		i += ft_putchar(num + '0');
	else
	{
		i += ft_putnbr(num / 10);
		i += ft_putchar((num % 10) + '0');
	}
	return (i);
}

static int	type(char c, va_list list)
{
	int	i;

	i = 0;
	if (c == 'c')
		i += ft_putchar(va_arg(list, int));
	else if (c == 's')
		i += ft_putstr(va_arg(list, char *));
	else if (c == 'd')
		i += ft_putnbr(va_arg(list, int));
	return (i);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	args;

	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			count += type(*(format + 1), args);
			format += 2;
		}
		else
		{
			count += ft_putchar(*format);
			format++;
		}
	}
	va_end(args);
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zminhas <zminhas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:03:24 by zminhas           #+#    #+#             */
/*   Updated: 2021/10/22 13:45:08 by zminhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

va_list	arg;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	if (str)
	{
		i = -1;
		while (str[++i])
			ft_putchar(str[i]);
	}
}

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	intlen(int nb)
{
	int	len;

	len = nb < 0 ? 1 : 0;
	while (nb /= 10)
		len++;
	return (++len);
}

void	ft_putnbr(int nb)
{
	if (nb < 0)
	{
		nb *= -1;
		ft_putchar('-');
	}
	if (nb > 9)
		ft_putnbr(nb / 10);
	ft_putchar('0' + nb % 10);
}

int	hexlen(int nb)
{
	int len;

	len = 0;
	while (nb /= 16)
		len++;
	return (++len);
}

int	percent_x(unsigned int nb, char *base)
{
	char	*res;
	int	power;
	int	i;

	power = hexlen(nb);
	res = (malloc(sizeof(char) * (power + 1)));
	if (!res)
		return(-1);
	i = power;
	while (power--)
	{
		res[power] = base[nb % 16];
		nb /= 16;
	}
	ft_putstr(res);
	free(res);
	return (i);
}

int	percent_d(int nb)
{
	ft_putnbr(nb);
	return (intlen(nb));
}

int	percent_s(char *str)
{
	if (!str)
	{
		ft_putstr("(null)");
		return (6);
	}
	ft_putstr(str);
	return (ft_strlen(str));
}

int	percent_all(char c)
{
	if (c == 'd')
		return (percent_d(va_arg(arg, int)));
	else if (c == 's')
		return (percent_s(va_arg(arg, char *)));
	else if (c == 'x')
		return (percent_x(va_arg(arg, unsigned int), "0123456789abcdef"));
	else
		return (-1);
}

int	ft_printf(const char *format, ...)
{
	int	total;
	int	checker;

	if (!*format)
		return (0);
	va_start(arg, format);
	total = 0;
	while (*format)
	{
		checker = 0;
		if (*format == '%')
		{
			format++;
			if ((checker = percent_all(*format)) == -1)
				return (total);
		}
		else
		{
			ft_putchar(*format);
			total++;
		}
		total += checker;
		format++;
	}
	va_end(arg);
	return (total);
}


/*#include <stdio.h>

int	main(void)
{
	printf("\nlen = %d\n", printf("salut c'est %x", -256256));
	printf("\nfake len = %d\n", ft_printf("salut c'est %x", -256256));
}*/
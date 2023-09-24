/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:19:58 by aamhal            #+#    #+#             */
/*   Updated: 2022/11/16 09:20:25 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_check(char c, va_list args, int *count)
{
	if (c == 'c')
		ft_putchar(va_arg(args, int), count);
	else if (c == 's')
		ft_putstr(va_arg(args, char *), count);
	else if (c == 'p')
	{
		ft_putstr("0x", count);
		ft_putadress(va_arg(args, unsigned long long), count);
	}
	else if (c == 'd')
		ft_putnbr(va_arg(args, unsigned int), count);
	else if (c == 'i')
		ft_putnbr(va_arg(args, int), count);
	else if (c == 'u')
		ft_putunbr(va_arg(args, unsigned int), count);
	else if (c == 'x')
		ft_puthexa(va_arg(args, unsigned int), count, 'l');
	else if (c == 'X')
		ft_puthexa(va_arg(args, unsigned int), count, 'u');
	else
		ft_putchar(c, count);
}

int	ft_printf(const char *s, ...)
{
	int		count;
	int		i;
	va_list	args;

	count = 0;
	i = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			if (!s[i + 1])
				return (count);
			ft_check(s[i + 1], args, &count);
			i++;
		}
		else
			ft_putchar(s[i], &count);
	i++;
	}
	va_end(args);
	return (count);
}

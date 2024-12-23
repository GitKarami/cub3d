/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 13:16:16 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/02/16 16:42:18 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/ft_printf.h"

void	ft_formatcheck(const char format, va_list args, int *printlen)
{
	if (format == 'c')
		ft_putchar(va_arg(args, int), printlen);
	else if (format == 's')
		ft_putstr(va_arg(args, char *), printlen);
	else if (format == 'p')
		ft_putptr(va_arg(args, unsigned long), printlen);
	else if (format == 'd' || format == 'i')
		ft_putnbr(va_arg(args, int), printlen);
	else if (format == 'u')
		ft_putuint(va_arg(args, unsigned int), printlen);
	else if (format == 'x' || format == 'X')
		ft_puthex(va_arg(args, unsigned int), format, printlen);
	else if (format == '%')
		ft_putchar('%', printlen);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		printlen;
	va_list	args;

	i = 0;
	printlen = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			ft_formatcheck(str[i + 1], args, &printlen);
			i++;
		}
		else
			ft_putchar(str[i], &printlen);
		i++;
	}
	va_end(args);
	return (printlen);
}

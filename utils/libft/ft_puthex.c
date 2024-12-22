/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_puthex.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 17:06:08 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/02/16 16:34:31 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/ft_printf.h"

void	ft_puthex(unsigned int n, char format, int *printlen)
{
	char	*hex;

	if (format == 'x')
	{
		hex = "0123456789abcdef";
	}
	else if (format == 'X')
	{
		hex = "0123456789ABCDEF";
	}
	if (n >= 16)
	{
		ft_puthex(n / 16, format, printlen);
		ft_puthex(n % 16, format, printlen);
	}
	if (n < 16)
		ft_putchar(hex[n], printlen);
}

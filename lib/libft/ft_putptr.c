/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putptr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 19:15:35 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/02/16 16:34:39 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/ft_printf.h"

void	ft_putptrhex(unsigned long n, int *printlen)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (n >= 16)
	{
		ft_putptrhex(n / 16, printlen);
		ft_putptrhex(n % 16, printlen);
	}
	if (n < 16)
		ft_putchar(hex[n], printlen);
}

void	ft_putptr(unsigned long ptr, int *printlen)
{
	if (ptr == 0)
		ft_putstr("(nil)", printlen);
	else
	{
		ft_putstr("0x", printlen);
		ft_putptrhex(ptr, printlen);
	}
}

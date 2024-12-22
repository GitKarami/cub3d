/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 17:06:11 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/02/16 16:34:36 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/ft_printf.h"

void	ft_putnbr(int n, int *printlen)
{
	if (n == INT_MIN)
	{
		ft_putstr("-2147483648", printlen);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-', printlen);
		n = -n;
	}
	if (n <= 9)
	{
		ft_putchar(n + '0', printlen);
	}
	else
	{
		ft_putnbr(n / 10, printlen);
		ft_putnbr(n % 10, printlen);
	}
}

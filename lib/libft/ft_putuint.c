/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putuint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 17:06:20 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/02/16 16:34:46 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/ft_printf.h"

void	ft_putuint(unsigned int n, int *printlen)
{
	if (n <= 9)
	{
		ft_putchar(n + '0', printlen);
	}
	else
	{
		ft_putnbr(n / 10, printlen);
		ft_putnbr(n % 10, printlen);
	}
	return ;
}

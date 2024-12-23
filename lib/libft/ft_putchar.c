/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putchar.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 15:18:07 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/02/16 16:34:27 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/ft_printf.h"

void	ft_putchar(int c, int *printlen)
{
	write(1, &c, 1);
	(*printlen)++;
}

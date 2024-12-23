/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 17:06:17 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/02/16 16:34:43 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/ft_printf.h"

void	ft_putstr(char *s, int *printlen)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		ft_putstr("(null)", printlen);
		return ;
	}
	while (s[i])
	{
		ft_putchar(s[i], printlen);
		i++;
	}
}

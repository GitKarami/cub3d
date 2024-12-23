/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalnum.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 13:29:48 by kchahmi       #+#    #+#                 */
/*   Updated: 2023/11/04 20:34:21 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 97 && c <= 'z') || (c >= 65 && c <= 90) || (c >= 48 && c <= 57))
	{
		return (1);
	}
	else
		return (0);
}

// int main(void)
// {
// 	int c = '2';
// 	printf("%d", ft_isalnum(c));
// 	return (0);
// }

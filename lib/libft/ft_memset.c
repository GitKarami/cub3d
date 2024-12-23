/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 14:06:48 by kchahmi       #+#    #+#                 */
/*   Updated: 2023/11/04 20:32:47 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	value;

	value = (unsigned char)c;
	ptr = (unsigned char *)str;
	while (n-- > 0)
		*ptr++ = value;
	return (str);
}

// int	main(void)
// {
// 	char	buffer[20];
// 	ft_memset(buffer, 'A', sizeof(buffer));
// 	return(0);
// }

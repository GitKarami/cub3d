/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 14:48:26 by kchahmi       #+#    #+#                 */
/*   Updated: 2023/11/04 20:33:03 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (n > i)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (&((unsigned char *)s)[i]);
		i++;
	}
	return (0);
}

// int main(void)
// {
// 	unsigned char *str = "HELLOOOO";
// 	printf("%s",(unsigned char *)ft_memchr(str, 'O', 6));
// 	return(0);
// }
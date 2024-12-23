/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 17:14:52 by kchahmi       #+#    #+#                 */
/*   Updated: 2023/11/04 20:32:54 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	if (!src && !dest)
		return (NULL);
	while (n--)
	{
		*d = *s;
		d++;
		s++;
	}
	return (dest);
}

// int main(void)
// {
// 	char	src[] = "Hello, WOrld!";
// 	char	dest[20];

// 	ft_memcpy(dest, src, sizeof(src));
// 	printf("%s\n", dest);
// 	return (0);
// }

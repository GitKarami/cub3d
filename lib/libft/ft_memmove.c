/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 11:39:19 by kchahmi       #+#    #+#                 */
/*   Updated: 2023/10/23 13:19:08 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (src < dest)
	{
		while (n--)
		{
			((unsigned char *)dest)[n] = ((const unsigned char *)src)[n];
		}
	}
	else if (src > dest)
	{
		while (n--)
		{
			((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}

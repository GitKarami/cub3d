/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 11:53:13 by kchahmi       #+#    #+#                 */
/*   Updated: 2023/11/04 20:32:58 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	const unsigned char	*str1_ptr;
	const unsigned char	*str2_ptr;

	str1_ptr = (const unsigned char *)str1;
	str2_ptr = (const unsigned char *)str2;
	while (n--)
	{
		if (*str1_ptr != *str2_ptr)
			return ((int)(*str1_ptr) - (int)(*str2_ptr));
		str1_ptr++;
		str2_ptr++;
	}
	return (0);
}

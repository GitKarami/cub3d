/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 17:01:19 by kchahmi       #+#    #+#                 */
/*   Updated: 2023/10/23 13:14:57 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	while (n--)
	{
		if (*str1 != *str2)
			return ((unsigned char)(*str1) - (unsigned char)(*str2));
		if (*str1 == '\0')
			return (0);
		str1++;
		str2++;
	}
	return (0);
}

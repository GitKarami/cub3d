/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 15:19:14 by kchahmi       #+#    #+#                 */
/*   Updated: 2023/11/04 20:32:17 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	k;
	size_t	i;
	size_t	j;

	k = 0;
	i = 0;
	j = 0;
	while (src[k])
		k++;
	while (dst[i])
		i++;
	if (size == 0)
		return (k);
	if (size <= i)
		return (size + k);
	while ((src[j]) && (j + i < size - 1))
	{
		dst[i + j] = *((char *)src + j);
		j++;
	}
	if (i < size)
		dst[i + j] = '\0';
	return (k + i);
}

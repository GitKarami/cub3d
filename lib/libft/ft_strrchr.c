/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 15:02:08 by kchahmi       #+#    #+#                 */
/*   Updated: 2023/10/23 13:15:13 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	c %= 256;
	while (i >= 0)
	{
		if (str[i] == (unsigned char)c)
		{
			return ((char *)&str[i]);
		}
		i--;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 13:42:11 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/08/10 15:03:50 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
		i++;
	return (i);
}

// int	main(void)
// {
// 	const char	*str = "hello!";
// 	printf("%d", ft_strlen(str));
// 	return (0);
// }
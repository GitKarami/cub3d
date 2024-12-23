/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 17:31:23 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/08/10 12:48:54 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *save, char *buffer)
{
	size_t	i;
	size_t	c;
	char	*str;

	if (!save)
	{
		save = (char *)malloc(1 * sizeof(char));
		if (!save)
			return (NULL);
		save[0] = '\0';
	}
	if (!buffer)
		return (free (save), NULL);
	str = malloc((ft_strlen(save) + ft_strlen(buffer) + 1) * sizeof(char));
	if (str == NULL)
		return (free(save), NULL);
	i = -1;
	c = 0;
	if (save)
		while (save[++i] != '\0')
			str[i] = save[i];
	while (buffer[c] != '\0')
		str[i++] = buffer[c++];
	str[ft_strlen(save) + ft_strlen(buffer)] = '\0';
	return (free(save), str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 12:28:50 by kchahmi       #+#    #+#                 */
/*   Updated: 2023/11/04 20:32:27 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *string)
{
	size_t	length;
	char	*duplicate;
	size_t	i;

	i = 0;
	length = ft_strlen(string);
	duplicate = (char *)malloc((length + 1) * sizeof(char));
	if (duplicate == NULL || string == NULL)
		return (NULL);
	while (string[i])
	{
		duplicate[i] = string[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

// int main(void)
// {
// 	const char *original = "Hello, world!";
// 	char *duplicate = ft_strdup(original);

// 	if(duplicate != NULL)
// 	{
// 		printf("Original: %s\n", original);
// 		printf("Duplicate: %s\n", duplicate);

// 		free(duplicate);
// 	} else
// 		printf("Memory allocation failed. \n");
// 	return (0);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 16:52:04 by kchahmi       #+#    #+#                 */
/*   Updated: 2023/11/04 20:31:28 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	substring = (char *)malloc(len + 1);
	if (!substring)
		return (NULL);
	i = 0;
	while (s[start] && len--)
	{
		substring[i] = s[start];
		start++;
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

// int main(void)
// {
// 	char const *string = "this is the substring!";
// 	unsigned int starter  = 3;
// 	size_t length = 5;
// 	char *array = ft_substr(string, starter, length);
// 	printf("%s", array);
// 	return(0);
// }
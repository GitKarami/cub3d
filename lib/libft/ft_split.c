/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 14:57:48 by kchahmi       #+#    #+#                 */
/*   Updated: 2023/11/04 20:31:03 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_free(char **array, int count)
{
	while (count >= 0)
		free(array[count--]);
	free(array);
	return (1);
}

static int	ft_isdelimiter(char c, char delimiter)
{
	if (c == delimiter)
		return (1);
	return (0);
}

static int	ft_word_count(const char *s, char c)
{
	int	start;
	int	word_count;

	word_count = 0;
	start = 0;
	while (s[start])
	{
		while (ft_isdelimiter(s[start], c) == 1)
			start++;
		if (s[start])
		{
			word_count++;
			while (s[start] && ft_isdelimiter(s[start], c) == 0)
				start++;
		}
	}
	return (word_count);
}

static char	**ft_filler(char **r, char const *s, char c)
{
	int	start;
	int	end;
	int	i;

	i = 0;
	start = 0;
	end = 0;
	while (s[start])
	{
		while (ft_isdelimiter(s[start], c) == 1)
			start++;
		if (s[start])
		{
			end = start;
			while (s[end] && s[end] != c)
				end++;
			r[i] = ft_substr(s, start, end - start);
			if (r[i] == NULL && ft_free(r, i) == 1)
				return (NULL);
			i++;
			start = end;
		}
	}
	return (r);
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**result;

	if (s == NULL)
		return (NULL);
	word_count = ft_word_count(s, c);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (result == NULL)
		return (result);
	result = ft_filler(result, s, c);
	if (result == NULL)
		return (NULL);
	result[word_count] = NULL;
	return (result);
}

// int main(void)
// {
// 	size_t i = 0;
// 	char **stringarray = ft_split(",,,,,,,,,,,,,,,,,", ',');
// 	printf("%s", stringarray[0]);
// 	while(stringarray[i])
// 	{
// 		printf("%s\n", stringarray[i]);
// 		i++;
// 	}
// 	return(0);
// }
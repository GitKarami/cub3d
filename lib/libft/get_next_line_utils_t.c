/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_t.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/10 15:06:38 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/08/11 17:12:36 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ftt_strclr(char *s)
{
	if (s)
	{
		while (*s)
		{
			*s = '\0';
			s++;
		}
	}
}

char	*ftt_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	else
		return (0);
}

void	ftt_memdel(void **ap)
{
	if (ap != NULL)
	{
		free(*ap);
		*ap = NULL;
	}
}

void	ftt_strdel(char **as)
{
	ftt_memdel((void **)as);
}

char	*ftt_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*res;
	size_t	len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ftt_strlen(s1) + ftt_strlen(s2);
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	res = str;
	while (*s1)
	{
		*str = *s1;
		str++;
		s1++;
	}
	while (*s2)
	{
		*str = *s2;
		str++;
		s2++;
	}
	*str = '\0';
	return (res);
}

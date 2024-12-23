/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 13:29:23 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/08/16 14:55:32 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h>
# include <stdio.h>
# include "ft_printf.h"
# define BUFF_SIZE 10

typedef struct s_arr
{
	int				fd;
	char			*rest;
	struct s_arr	*next;
}				t_arr;

typedef struct s_data
{
	char	*rest;
	char	buf[BUFF_SIZE + 1];
	char	*p_n;
	int		rd;
}	t_data;

int				ft_atoi(const char *str);

void			ft_bzero(void *s, size_t n);

void			*ft_calloc(size_t nmemb, size_t size);

int				ft_isalnum(int c);

int				ft_isalpha(int c);

int				ft_isascii(int c);

int				ft_isdigit(int c);

int				ft_isprint(int c);

char			*ft_itoa(int n);

void			*ft_memccpy(void *dst, const void *src, int c, size_t n);

void			*ft_memchr(const void *s, int c, size_t n);

int				ft_memcmp(const void *s1, const void *s2, size_t n);

void			*ft_memcpy(void *dst, const void *src, size_t n);

void			*ft_memmove(void *dst, const void *src, size_t len);

void			*ft_memset(void *b, int c, size_t len);

void			ft_putchar_fd(char c, int fd);

void			ft_putendl_fd(char *s, int fd);

void			ft_putnbr_fd(int n, int fd);

void			ft_putstr_fd(char *s, int fd);

char			**ft_split(char const *s, char c);

char			*ft_strchr(char *s, int c);

char			*ft_strdup(const char *s1);

char			*ft_strjoin(char *save, char *buffer);

size_t			ft_strlcat(char *dst, const char *src, size_t size);

size_t			ft_strlcpy(char *dst, const char *src, size_t size);

size_t			ft_strlen(const char *str);

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void			ft_striteri(char *s, void (*f)(unsigned int, char*));

int				ft_strncmp(const char *s1, const char *s2, size_t n);

char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);

char			*ft_strrchr(const char *s, int c);

char			*ft_strtrim(char *s1, char *set);

char			*ft_substr(char const *s, unsigned int start, size_t len);

int				ft_tolower(int c);

int				ft_toupper(int c);

char			*ftt_strnew(size_t size);
char			*ftt_strchr(const char *s, int c);
char			*ftt_strsub(char const *s, unsigned int start, size_t len);
char			*ftt_strcpy(char *dst, const char *src);
char			*ftt_strnew(size_t size);
char			*ftt_strcat(char *restrict str1, const char *restrict str2);
void			ftt_strclr(char *s);
char			*ftt_strchr(const char *s, int c);
void			ftt_memdel(void **ap);
void			ftt_strdel(char **as);
char			*ftt_strjoin(char const *s1, char const *s2);
size_t			ftt_strlen(const char *str);
int				get_next_line(const int fd, char **line);

#endif
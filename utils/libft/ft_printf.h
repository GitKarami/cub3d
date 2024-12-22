/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 15:19:19 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/01/24 19:00:14 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
void	ft_putchar(int c, int *printlen);
void	ft_putstr(char *s, int *printlen);
void	ft_putnbr(int n, int *printlen);
void	ft_putuint(unsigned int n, int *printlen);
void	ft_puthex(unsigned int n, char format, int *printlen);
void	ft_putptrhex(unsigned long n, int *printlen);
void	ft_putptr(unsigned long ptr, int *printlen);

#endif

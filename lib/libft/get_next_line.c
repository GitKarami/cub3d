/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 16:47:31 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/08/16 14:55:05 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_arr	*newlist(const int fd)
{
	t_arr	*new;

	new = (t_arr *)malloc(sizeof(t_arr));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->rest = ftt_strnew(BUFF_SIZE);
	new->next = NULL;
	return (new);
}

static char	*checkrest(char **p_n, char *rest)
{
	char	*str;

	*p_n = ftt_strchr(rest, '\n');
	if (*p_n != NULL)
	{
		str = ftt_strsub(rest, 0, *p_n - rest);
		ftt_strcpy(rest, ++(*p_n));
	}
	else
	{
		str = ftt_strnew(ftt_strlen(rest) + 1);
		ftt_strcat(str, rest);
		ftt_strclr(rest);
	}
	return (str);
}

static int	read_and_process(const int fd, char **line, t_data *data)
{
	char	*tmp;

	while (data->p_n == NULL)
	{
		data->rd = read(fd, data->buf, BUFF_SIZE);
		if (data->rd < 0)
			return (-1);
		if (data->rd == 0)
			break ;
		data->buf[data->rd] = '\0';
		data->p_n = ftt_strchr(data->buf, '\n');
		if (data->p_n != NULL)
		{
			ftt_strcpy(data->rest, data->p_n + 1);
			ftt_strclr(data->p_n);
		}
		tmp = *line;
		*line = ftt_strjoin(tmp, data->buf);
		ftt_strdel(&tmp);
		if (*line == NULL)
			return (-1);
	}
	return (0);
}

static int	get_line(const int fd, char **line, char *rest)
{
	t_data	data;

	data.p_n = NULL;
	data.rd = 1;
	data.rest = rest;
	*line = checkrest(&data.p_n, rest);
	if (*line == NULL)
		return (-1);
	if (read_and_process(fd, line, &data) == -1)
		return (-1);
	if (ftt_strlen(*line) > 0 || ftt_strlen(rest) > 0 || data.rd != 0)
		return (1);
	else
		return (0);
}

int	get_next_line(const int fd, char **line)
{
	static t_arr	*list;
	t_arr			*tmp;
	int				ret;

	if (fd < 0 || line == 0)
		return (-1);
	if (!list)
		list = newlist(fd);
	tmp = list;
	while (tmp->fd != fd)
	{
		if (tmp->next == NULL)
			tmp->next = newlist(fd);
		tmp = tmp->next;
	}
	ret = get_line(fd, line, tmp->rest);
	return (ret);
}

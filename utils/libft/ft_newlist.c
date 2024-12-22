/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_newlist.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 17:05:44 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/08/20 17:08:52 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_arr	*newlist(const int fd)
{
	t_arr	*new;

	new = (t_arr *)malloc(sizeof(t_arr));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->rest = ftt_strnew(BUFF_SIZE);
	if (new->rest == NULL)
		return (NULL);
	new->next = NULL;
	return (new);
}

void	clean_up_node(t_arr **list, t_arr *tmp)
{
	t_arr	*prev;

	if (tmp == *list)
		*list = (*list)->next;
	else
	{
		prev = *list;
		while (prev->next != tmp)
			prev = prev->next;
		prev->next = tmp->next;
	}
	free(tmp->rest);
	free(tmp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_freelist.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 15:32:15 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/08/20 17:13:05 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_linked_list(t_arr *head)
{
	t_arr	*current;

	while (head != NULL)
	{
		current = head;
		head = head->next;
		if (current->rest != NULL)
			free(current->rest);
		free(current);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 19:17:31 by mqian             #+#    #+#             */
/*   Updated: 2019/03/14 18:51:07 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *curr;
	t_list *track;
	t_list *head;

	track = NULL;
	head = NULL;
	while (lst && f)
	{
		if (!(curr = ft_lstnew(((f)(lst))->content, ((f)(lst))->content_size)))
			return (NULL);
		if (!track)
		{
			head = curr;
			track = curr;
			curr = curr->next;
		}
		else
		{
			track->next = curr;
			curr = curr->next;
			track = track->next;
		}
		lst = lst->next;
	}
	return (head);
}
/*
** Iterates a list lst and applies the function f to each link to
** create a “fresh” list (using malloc(3)) resulting from the
** successive applications of f. If the allocation fails, the function
** returns NULL
** allocates mem for new elem. if it fails at any point, return NULL; wont
** there be memory left dangling if it allocates some and then it doesnt
** allocate
** one and returns NULL?
** if (!track) line is to handle for first time you create elem
** sets head and track to curr. curr moves to next elem;
** every other time the loop points the element befores next to the curr
** that was just created.
** then curr moves and track moves too;
** lst is moved at the end of the loop to get the next element of the list
** we are referencing
** return (head). head will be null if lst && func are NULL;
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 19:27:33 by mqian             #+#    #+#             */
/*   Updated: 2019/03/14 18:46:15 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *,
size_t))
{
	t_list *temp;

	temp = *alst;
	while (temp)
	{
		(del)((temp)->content, (temp)->content_size);
		temp = temp->next;
		free(*alst);
		*alst = temp;
	}
	free(*alst);
	*alst = NULL;
}

/*
** have a pointer be the curr that deletes
** original alst tracks the temp and gets freed
** while (temp), del function is used on list element, temp moves over,
** free (*alst) frees memory of the element that del function was just used
** on, then alst moved up to temp
** repeat until temp reaches null
** free last element pointed to by alst then point it to null
*/

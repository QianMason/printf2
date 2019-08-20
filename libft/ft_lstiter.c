/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 19:18:33 by mqian             #+#    #+#             */
/*   Updated: 2019/03/12 17:12:36 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list
*elem))
{
	while (lst && f)
	{
		(f)(lst);
		lst = lst->next;
	}
}

/*
** iterates through the list and applies function to each element
** apply function to element, then set list to its next element
** rinse and repeat
*/

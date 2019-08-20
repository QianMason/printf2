/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 17:27:53 by mqian             #+#    #+#             */
/*   Updated: 2019/03/14 21:37:53 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*alloc;
	int		i;

	i = 0;
	alloc = (void *)malloc(sizeof(char) * size);
	if (!alloc)
	{
		return (NULL);
	}
	ft_bzero(alloc, size);
	return (alloc);
}

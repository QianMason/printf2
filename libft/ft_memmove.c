/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 12:44:11 by mqian             #+#    #+#             */
/*   Updated: 2019/03/14 18:47:27 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int				i;
	unsigned char	*dt;
	unsigned char	*st;

	dt = (unsigned char *)dst;
	st = (unsigned char *)src;
	i = len;
	if (st >= dt)
		ft_memcpy(dst, src, len);
	else
	{
		while (i - 1 >= 0)
		{
			dt[i - 1] = st[i - 1];
			i--;
		}
	}
	return (dst);
}

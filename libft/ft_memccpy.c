/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:55:21 by mqian             #+#    #+#             */
/*   Updated: 2019/03/14 18:50:38 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			len;
	unsigned char	*s;
	unsigned char	*d;

	d = dst;
	s = (unsigned char *)src;
	len = 0;
	while (len < n)
	{
		*d = *s;
		if (*s == (unsigned char)c)
		{
			d++;
			return ((void *)d);
		}
		d++;
		s++;
		len++;
	}
	return (NULL);
}

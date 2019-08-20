/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 19:54:47 by mqian             #+#    #+#             */
/*   Updated: 2019/03/14 18:48:51 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		max;
	size_t		len;
	size_t		dstlen;

	dstlen = ft_strlen(dst);
	if (dstsize <= ft_strlen(dst))
		return (ft_strlen(src) + dstsize);
	max = dstsize - ft_strlen(dst) - 1;
	len = 0;
	while (*dst != '\0')
		dst++;
	while (src[len] && len < max)
	{
		dst[len] = src[len];
		len++;
	}
	dst[len] = '\0';
	return (dstlen + ft_strlen(src));
}

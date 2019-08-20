/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:40:13 by mqian             #+#    #+#             */
/*   Updated: 2019/03/14 18:49:13 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	char	*s;
	char	*d;
	size_t	srclen;

	s = (char *)src;
	d = (char *)dst;
	i = 0;
	srclen = ft_strlen(src);
	while (i < len && i < srclen)
	{
		*d = *s;
		i++;
		s++;
		d++;
	}
	while (i < len)
	{
		*d = '\0';
		d++;
		i++;
	}
	return (dst);
}

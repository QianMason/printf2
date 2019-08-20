/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:14:47 by mqian             #+#    #+#             */
/*   Updated: 2019/03/14 18:49:25 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hstk, const char *needle, size_t len)
{
	size_t	searchlen;
	size_t	remainlen;

	remainlen = len;
	searchlen = ft_strlen(needle);
	if (searchlen < 1)
		return ((char *)hstk);
	while (*hstk && remainlen >= searchlen)
	{
		if (*hstk == *needle && ft_memcmp(hstk, needle, searchlen) == 0)
			return ((char *)hstk);
		hstk++;
		remainlen--;
	}
	return (NULL);
}

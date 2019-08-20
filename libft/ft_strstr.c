/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:41:00 by mqian             #+#    #+#             */
/*   Updated: 2019/03/14 18:49:40 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char *ht;
	char *nt;

	ht = (char *)haystack;
	nt = (char *)needle;
	if (ft_strlen(needle) < 1)
		return ((char *)haystack);
	while (*ht)
	{
		if (*ht == *nt)
		{
			if (ft_strstrhelper(ht, nt))
			{
				return (ht);
			}
		}
		ht++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 19:03:47 by mqian             #+#    #+#             */
/*   Updated: 2019/03/14 18:49:17 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t len;

	len = 0;
	if (!s1 || !s2)
		return (0);
	while (*s1 && *s2 && len < n)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
		len++;
	}
	return (1);
}

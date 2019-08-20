/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 17:37:17 by mqian             #+#    #+#             */
/*   Updated: 2019/03/14 18:48:03 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int desti;
	int srci;

	desti = 0;
	srci = 0;
	while (s1[desti] != '\0')
		desti++;
	while (s2[srci] != '\0')
	{
		s1[desti] = s2[srci];
		srci++;
		desti++;
	}
	s1[desti] = '\0';
	return (s1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 19:26:22 by mqian             #+#    #+#             */
/*   Updated: 2019/03/14 18:48:48 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	char	*temp;

	new = NULL;
	if (s1 && s2)
	{
		temp = ft_strnew(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)));
		if (!temp)
			return (NULL);
		new = temp;
		while (*s1)
		{
			*temp = *s1;
			s1++;
			temp++;
		}
		while (*s2)
		{
			*temp = *s2;
			s2++;
			temp++;
		}
	}
	return (new);
}

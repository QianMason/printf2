/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 19:25:05 by mqian             #+#    #+#             */
/*   Updated: 2019/03/14 18:49:50 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		front;
	int		back;
	int		len;
	char	*new;

	if (!s)
		return (NULL);
	front = ft_strtrimfronthelper((char *)s);
	if (front < 0)
	{
		new = ft_strnew(0);
		return (new);
	}
	back = ft_strtrimbackhelper((char *)s);
	len = ft_strlen((char *)s);
	new = ft_strsub(s, front, (len - front - back));
	if (!new)
		return (NULL);
	return (new);
}

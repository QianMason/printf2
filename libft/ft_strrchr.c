/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 18:13:50 by mqian             #+#    #+#             */
/*   Updated: 2019/03/14 18:49:28 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	*temp;
	size_t	i;

	i = 0;
	len = ft_strlen((char *)s);
	temp = NULL;
	if ((char)c == '\0')
		return ((char *)s + len);
	while (i < len)
	{
		if (s[i] == (char)c)
			temp = (char *)&s[i];
		i++;
	}
	if (temp == NULL)
		return (NULL);
	return (temp);
}

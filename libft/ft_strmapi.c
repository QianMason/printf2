/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 18:08:26 by mqian             #+#    #+#             */
/*   Updated: 2019/03/14 18:49:03 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*new;

	if (!s || !f)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	new = (char *)ft_strnew(len);
	if (!new)
		return (NULL);
	while (i < len)
	{
		new[i] = (f)((unsigned int)i, s[i]);
		i++;
	}
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 19:24:49 by mqian             #+#    #+#             */
/*   Updated: 2019/03/14 18:49:47 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	new = (char *)ft_strnew(sizeof(char) * len);
	i = 0;
	if (!new || !s)
		return (NULL);
	while (i < len && s[start])
		new[i++] = s[start++];
	return (new);
}

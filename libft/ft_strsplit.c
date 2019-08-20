/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 19:13:05 by mqian             #+#    #+#             */
/*   Updated: 2019/03/14 18:49:36 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_nextindex(char *s, char c, int idx)
{
	while (s[idx] && s[idx] == c)
		idx++;
	return (idx);
}

static	int	ft_getlen(char *s, char c, int idx)
{
	int	len;

	len = 0;
	while (s[idx])
	{
		if (s[idx] != c)
			len++;
		idx++;
	}
	return (len);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**new;
	int		idx;
	int		wordcount;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	wordcount = ft_wordcount((char *)s, c);
	i = 0;
	idx = 0;
	if (!(new = (char **)malloc(sizeof(s) * (wordcount + 1))))
		return (NULL);
	while (i < wordcount)
	{
		j = 0;
		idx = ft_nextindex((char *)s, c, idx);
		if (!(new[i] = ft_strnew(sizeof(char) * ft_getlen((char *)s, c, idx))))
			return (NULL);
		while (s[idx] != c && s[idx])
			new[i][j++] = s[idx++];
		i++;
	}
	new[i] = 0;
	return (new);
}

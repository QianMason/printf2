/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:38:08 by mqian             #+#    #+#             */
/*   Updated: 2019/03/07 18:18:15 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int				sign;
	int				n;
	const char		*copy;

	copy = str;
	sign = 1;
	n = 0;
	while (*copy == '\n' || *copy == ' ' || *copy == '\t' ||
			*copy == '\r' || *copy == '\f' || *copy == '\v')
		copy++;
	if (*copy == '-' || *copy == '+')
	{
		if (*copy == '-')
			sign = -1;
		copy++;
	}
	while ((*copy) >= '0' && *copy <= '9')
	{
		n = (n * 10) + (*copy - '0');
		copy++;
	}
	return (n * sign);
}

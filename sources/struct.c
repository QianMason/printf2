/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 16:46:48 by mqian             #+#    #+#             */
/*   Updated: 2019/08/19 15:21:47 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_print *init_struct(t_print *p, char *format)
{
	if (!(p = (t_print *)malloc(sizeof(t_print))))
		return (NULL);
	p->format = format;
	init_dispatch_table(p->formatters);
	p->count = 0;
	reset_flags(p);
	return (p);
}

void	reset_flags(t_print *p)
{
	int i;

	i = 0;
	while (i < 10)
	{
		p->flags[i] = 0;
		i++;
	}
}

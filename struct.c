/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 16:46:48 by mqian             #+#    #+#             */
/*   Updated: 2019/07/24 20:42:12 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_print_struct *init_struct(t_print_struct *p, char *format, va_list args)
{
	int i;

	i = 0;
	if (!(p = (t_print_struct *)malloc(sizeof(t_print_struct))))
		return (NULL);
	p->format = format;
	init_dispatch_table(p->formatters);
	p->count = 0;
	reset_flags(p);
	return (p);
}

void	reset_flags(t_print_struct *p)
{
	int i;

	i = 0;
	while (i < 10)
	{
		p->flags[i] = 0;
		i++;
	}
}

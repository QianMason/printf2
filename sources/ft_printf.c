/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 16:44:14 by mqian             #+#    #+#             */
/*   Updated: 2019/08/19 17:07:10 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	t_print			*print;
	va_list			args;

	print = NULL;
	va_start(args, format);
	print = init_struct(print, (char*)format);
	print->count = parse_and_print(print, args);
	return (print->count);
}

/**
*the limitation i can see with my implementation is the
*the large of amounts of branches / chains of if else logic
*another limitation is since it writes each character one at a time instead of
*buffering and printing whole blocks,
*if you try to print a large piece of text with thousands of characters, it
*will be much slower than an implementation
*that generates the string in memory and prints the block of memory based on
*the length of the string
*an advantage I have is memory overhead. I never call malloc a single time.
*but does this mean I should follow the adage of my old CS professor from CS125?
*"Space is cheap, time is not." - Bill Chapman
**/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 16:44:14 by mqian             #+#    #+#             */
/*   Updated: 2019/07/15 16:49:12 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
    int count;
    t_print_struct  *print;
    va_list         args;

    count = 0;
    va_start(args, format);
    print = init_struct(print, (char*)format, args);
    count = parse_and_print(print, args, count);
    return (count);
}


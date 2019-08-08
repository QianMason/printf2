/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_f_helpers_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 16:47:24 by mqian             #+#    #+#             */
/*   Updated: 2019/08/07 17:01:44 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     format_f_left(int flags[], char *f_string, long double arg)
{
    int count;
    intmax_t hold;

    hold = (intmax_t)arg;
    count += format_d_sign(flags, &hold);
    count += ft_printf("%s", f_string);
    while (count < flags[5])
        count += write_and_increment(' ');
    return (count);
}

int     format_f_right(int flags[], char *f_string, int len, long double arg)
{
    int count;
    intmax_t hold;

    hold = (intmax_t)arg;
    count = 0;
    while (count < flags[5] - len - 1)
        count += (flags[3] == 1 && flags[6] == 0) ? write_and_increment('0') : write_and_increment(' ');
    if (format_d_sign(flags, &hold) == 1)
        count += 1;
    else
        count += write_and_increment(' ');
    count += ft_printf("%s", f_string);
    return (count);
}
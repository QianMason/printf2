/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_f_helpers_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 16:47:24 by mqian             #+#    #+#             */
/*   Updated: 2019/08/19 14:59:51 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		format_f_left(int flags[], char *f_string, long double arg)
{
    int			count;
    intmax_t	hold;

    count = 0;
    hold = (intmax_t)arg;
    count += format_d_sign(flags, &hold);
    ft_putstr(f_string);
    count += ft_strlen(f_string);
    while (count < flags[5])
        count += write_and_increment(' ');
    return (count);
}

int		format_f_right(int flags[], char *f, int len, long double arg)
{
    int count;

    count = 0;
    if (flags[3] == 1) //0 pad
    {
        if (arg < 0)
            count += write_and_increment('-');
        else if (flags[0])
            count += write_and_increment('+');
        else if (flags[4])
            count += write_and_increment(' ');
        while (count < flags[5] - len)
            count += (flags[3] == 1) ? write_and_increment('0') : write_and_increment(' ');
    }
    else
    {
        while (count < flags[5] - len - 1)
            count += write_and_increment(' ');
        if (arg < 0)
            count += write_and_increment('-');
        else if (flags[0])
            count += write_and_increment('+');
        else if (flags[4])
            count += write_and_increment(' ');
        while (count < flags[5] - len)
            count += write_and_increment(' ');
    }
    ft_putstr(f);
    count += ft_strlen(f);
    return (count);
}

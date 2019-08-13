/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_f_helpers_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 16:47:24 by mqian             #+#    #+#             */
/*   Updated: 2019/08/12 16:56:58 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     format_f_left(int flags[], char *f_string, long double arg)
{
    int count;
    intmax_t hold;

    hold = (intmax_t)arg;
    count += format_d_sign(flags, &hold);
    ft_putstr(f_string);
    count += ft_strlen(f_string);
    while (count < flags[5])
        count += write_and_increment(' ');
    return (count);
}

int     format_f_right(int flags[], char *f_string, int len, long double arg)
{
    int count;
    intmax_t hold;
    printf("in here\n");
    hold = (intmax_t)arg;
    count = 0;
    if (flags[3] == 1) //0 pad
    {
        if (flags[5] - len - 1 >= 0)
        {
            if (format_d_sign(flags, &hold) == 1)
                count += 1;
            else
                count += write_and_increment(' ');
        }
        else
        {
            if (format_d_sign(flags, &hold) == 1)
                count += 1;
        }
        while (count < flags[5] - len)
            count += (flags[3] == 1) ? write_and_increment('0') : write_and_increment(' ');
    }
    else
    {
        while (count < flags[5] - len - 1)
            count += (flags[3] == 1) ? write_and_increment('0') : write_and_increment(' ');
        if (flags[5] - len - 1 >= 0)
        {
            if (format_d_sign(flags, &hold) == 1)
                count += 1;
            else
                count += write_and_increment(' ');
        }
        else
        {
            if (format_d_sign(flags, &hold) == 1)
                count += 1;
        }
    }
    ft_putstr(f_string);
    count += ft_strlen(f_string);
    return (count);
}
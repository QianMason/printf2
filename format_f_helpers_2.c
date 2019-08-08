/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_f_helpers_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:49:48 by mqian             #+#    #+#             */
/*   Updated: 2019/08/07 17:46:18 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     format_f_special(int flags[], long double argument, int count)
{
    intmax_t hold;

    hold = (f_prec_default(flags)) ? get_prec_num_f(argument, 6) : get_prec_num_f(argument, flags[7]);
    if (flags[1] == 1)
        return (f_special_left(flags, hold, count));
    else
        return (f_special_right(flags, hold, count));
}

int     f_special_left(int flags[], intmax_t hold, int count)
{
    int temp;

    temp = 0;
    count += format_d_sign(flags, &hold);
    write(1, "0.", 2);
    count += 2;
    while (temp++ < flags[7] - get_int_len(hold))
        count += write_and_increment('0');
    count += print_int_max(hold, 1);
    while (count < flags[5])
        count += write_and_increment(' ');
    return (count);
}

int     f_special_right(int flags, intmax_t hold, int count)
{
    int temp;

    temp = 0;
    count += format_d_sign(flags, &hold);
    while (count < flags[5] - (8))
        count += (flags[3] == 1 && flags[6] == 0) ? write_and_increment('0') : write_and_increment(' ');
    write(1, "0.", 2);
    count += 2;
    if (flags[3] == 1 && flags[6] == 0)
    {
        while (temp++ < 6 - get_int_len(hold))
            count += write_and_increment('0');
    }
    else
    {
        while (temp++ < flags[7] - get_int_len(hold))
            count += write_and_increment('0');
    }
    count += print_int_max(hold, 1);
    return (count);
}
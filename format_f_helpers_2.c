/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_f_helpers_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:49:48 by mqian             #+#    #+#             */
/*   Updated: 2019/08/12 15:24:57 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     format_f_special(int flags[], long double argument, int count)
{
    intmax_t hold;

    if (flags[6] == 0)
        hold = get_prec_num_f(argument, 6);
    else if (flags[6] == 1 && flags[7] == 0)
        hold = (intmax_t)argument;
    else
        hold = get_prec_num_f(argument, flags[7]);
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

// int     f_special_right(int flags[], intmax_t hold, int count)
// {
//     int temp;

//     temp = 0;
//     count += format_d_sign(flags, &hold);
//     while (count < flags[5] - (8))
//         count += (flags[3] == 1 && flags[6] == 0) ? write_and_increment('0') : write_and_increment(' ');
//     write(1, "0.", 2);
//     count += 2;
//     if (flags[3] == 1 && flags[6] == 0)
//     {
//         while (temp++ < 6 - get_int_len(hold))
//             count += write_and_increment('0');
//     }
//     else
//     {
//         while (temp++ < flags[7] - get_int_len(hold))
//             count += write_and_increment('0');
//     }
//     count += print_int_max(hold, 1);
//     return (count);
// }

int     f_special_right(int flags[], intmax_t hold, int count)
{
    int temp;

    temp = 0;
    if (flags[3] == 1)
    {
        count += format_d_sign(flags, &hold);
        while (count < flags[5] - 8)
            count += write_and_increment('0');
    }
    else
    {
        if (flags[6] == 0)
        {
            while (count < flags[5] - 9)
                count += write_and_increment(' ');
        }
        else
        {
            while (count < flags[5] - (3 + flags[7]))
                count += write_and_increment(' ');
        }
        if (format_d_sign(flags, &hold) == 1)
            count += 1;
        else
            count += write_and_increment(' ');
    }
    write(1, "0.", 2);
    count += 2;
    count += print_int_max(hold, 1);
    return (count);
}
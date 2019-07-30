/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_p_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 14:03:54 by mqian             #+#    #+#             */
/*   Updated: 2019/07/30 12:42:18 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// int     format_p_left_helper(int flags[], unsigned dec, int len)
// {
//     int count;

//     count = 0;
//     write(1, "0x", 2);
//     count += 2;
//     if (flags[5] > 0) //minw
//     {
//         count += convert_to_hex(dec, 1);
//         while (count < flags[5])
//         {
//             write(1, " ", 1);
//             count++;
//         }
//     }
//     else
//         count += convert_to_hex(dec, 1);
//     return (count);
// }

int     format_p_left(int flags[], uintmax_t dec, int len)
{
    int count;

    count = 0;
    write(1, "0x", 2);
    count += 2;
    if (len >= flags[5] && len >= flags[7])
        count += convert_to_hex(dec, 1);
    else if (flags[7] >= flags[5] && flags[7] >= len)
        count += format_p_left_helper_1(flags, dec, len);
    else if (flags[5] >= len && flags[5] >= flags[7])
    {
        if (len >= flags[7])
            count += format_p_left_helper_2(flags, dec, len);
        else // minw >= precision > len
            count += format_p_left_helper_3(flags, dec, len);
    }
    return (count);
}

int     format_p_left_helper_1(int flags[], uintmax_t dec, int len)
{
    // if precision is >= minw && >= arg_len
    // left aligned so no 0 consideration
    // but since precision might be greater, we print 0 until precision
    int count;

    count = 0;
    while (count < flags[7] - len)
        count += write_and_increment('0');
    count += convert_to_hex(dec, 1);
    return (count);
}

int format_p_left_helper_2(int flags[], uintmax_t dec, int len)
{
    //if minw >= len && minw >= precision
    //if len >= precision
    //left aligned
    int count;

    count += convert_to_hex(dec, 1);
    while (count + 2 < flags[5])
        count += write_and_increment(' ');
    return (count);
}

int format_p_left_helper_3(int flags[], uintmax_t dec, int len)
{
    // minw >= precision && minw >= arg_len
    // precision > arg_len
    int count;

    count = 0;
    while (count < flags[7] - len)
        count += write_and_increment('0');
    count += convert_to_hex(dec, 1);
    while (count + 2 < flags[5])
        count += write_and_increment(' ');
    return (count);
}

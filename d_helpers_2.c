/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_helpers_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 14:55:31 by mqian             #+#    #+#             */
/*   Updated: 2019/08/01 15:48:03 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     format_d_right(int flags[], intmax_t argument, int len)
{
    int count;

    count = 0;
    if (len >= flags[5] && len >= flags[7])
    {
        count = format_d_sign(flags, &argument); //writes the sign if its there
        count += print_uint_max(argument, 1);
    }    
    else if (flags[7] >= flags[5] && flags[7] >= len)
        count += format_d_right_helper_1(flags, argument, len); //maybe just switch to left one to save a function
    else if (flags[5] >= flags[7] && flags[5] >= len)
    {
        if (len >= flags[7])
            count += format_d_right_helper_2(flags, argument, len);
        else
            count += format_d_right_helper_3(flags, argument, len);
    }
    return (count);   
}

int     format_d_right_helper_1(int flags[], intmax_t argument, int len)
{
    //precision greatest
    //minw ignored
    //for format d, if precision is the greatest, then really its just the same case
    //for both left and right, so simply call the one you wrote already
    return (format_d_left_helper_1(flags, argument, len));
}

int     format_d_right_helper_2(int flags[], intmax_t argument, int len)
{
    //minw greatest
    //len >= precision so precision is ignored
    //must consider flags[3] since it could be zero padded
    int count;

    count = 0;
    if (flags[3] == 1 && flags[6] == 0 && flags[7] == 0)
    {
        count += format_d_sign(flags, &argument);
        while (count < flags[5] - len)
            count += write_and_increment('0');
        count += print_uint_max(argument, 1);
    }
    else
    {
        while (count < flags[5] - len - 1)
            count += write_and_increment(' ');
        if (format_d_sign(flags, &argument) == 1)
            count += 1;
        else
            count += write_and_increment(' ');
        count += print_uint_max(argument, 1);
    }
    return (count);
}

int     format_d_right_helper_3(int flags[], intmax_t argument, int len)
{
    //minw greatest
    //precision > len
    int count;

    count = 0;
    while (count < flags[5] - flags[7] - 1)
        count += write_and_increment(' ');
    if (format_d_sign(flags, &argument) == 1)
        count += 1;
    else
        count += write_and_increment(' ');
    while (count < flags[5] - len)
        count += write_and_increment('0');
    count += print_uint_max(argument, 1);
    return (count);
}
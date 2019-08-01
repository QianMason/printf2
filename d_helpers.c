/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_helpers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 13:09:09 by mqian             #+#    #+#             */
/*   Updated: 2019/08/01 16:03:57 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


int     format_d_left(int flags[], intmax_t argument, int len)
{
    int count;

    count = 0;
    if (len >= flags[5] && len >= flags[7])
    {
        count = format_d_sign(flags, &argument); //writes the sign if its there
        count += print_uint_max(argument, 1);
    }
    else if (flags[7] >= flags[5] && flags[7] >= len)
        count += format_d_left_helper_1(flags, argument, len);
    else if (flags[5] >= flags[7] && flags[5] >= len)
    {
        if (len >= flags[7])
            count += format_d_left_helper_2(flags, argument, len);
        else
            count += format_d_left_helper_3(flags, argument, len);
    }
    return (count);
}

int    format_d_left_helper_1(int flags[], intmax_t argument, int len)
{
    int count;

    count = format_d_sign(flags, &argument);
    if (count == 1) //which means we wrote something
    {
        while (count < flags[7] - len + 1)
            count += write_and_increment('0');
        count += print_uint_max(argument, 1);
    }
    else
    {
        while (count < flags[7] - len)
            count += write_and_increment('0');
        count += print_uint_max(argument, 1);
    }
    return (count);
}

int     format_d_left_helper_2(int flags[], intmax_t argument, int len)
{
    //len >= precision so precision is not considered
    //minw greatest
    int count;

    count = format_d_sign(flags, &argument);
    count += print_uint_max(argument, 1);
    while (count < flags[5])
        count += write_and_increment(' ');
    return (count);
}

int     format_d_left_helper_3(int flags[], intmax_t argument, int len)
{
    //minw >= precision && minw >= len
    //precision > len
    int count;

    count = format_d_sign(flags, &argument);
    if (count == 1) //which means we wrote something
    {
        while (count < flags[7] - len + 1)
            count += write_and_increment('0');
        count += print_uint_max(argument, 1);
    }
    else
    {
        while (count < flags[7] - len)
            count += write_and_increment('0');
        count += print_uint_max(argument, 1);
    }
    while (count < flags[5])
        count += write_and_increment(' ');
    return (count);
}

int    format_d_sign(int flags[], intmax_t *arg)
{
    int count;

    count = 0;
    if (*arg < 0) //negative the value is always written
    {
        count += write_and_increment('-');
        *arg *= -1;
    }
    else if (flags[0] == 1 && *arg > 0) //next in line is if there is a + flag, which means show the '+' if positive
        count += write_and_increment('+');
    else if (flags[4] == 1) //final check is if ' ' flag is present, then write in a space initially
        count += write_and_increment(' ');
    return (count);    
}
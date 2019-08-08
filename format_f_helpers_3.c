/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_f_helpers_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 13:34:44 by mqian             #+#    #+#             */
/*   Updated: 2019/08/07 17:46:20 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     f_test_zero(int flags[], long double argument)
{
    intmax_t hold;

    if (f_prec_default(flags))
        hold = get_prec_num_f(argument, 6);
    else
        hold = get_prec_num_f(argument, flags[7]);
    return (hold == 0) ? 0 : 1;
}

int     format_f_zero(int flags[])
{
    int count;

    count = 0;
    if (flags[1] == 1) //left justify
        count += format_f_zero_left(flags, count);
    else
        count += format_f_zero_right(flags, count);
    return (count);   
}

int     format_f_zero_left(int flags[], int count)
{
    if (flags[6] == 0) //precision not specified, so automatically given to be 6
    {
        write(1, "0.000000", 8);
        count += 8;
        while (count < flags[5])
            count += write_and_increment(' ');
    }
    else if (flags[6] == 1 && flags[7] == 0)
    {
        count += write_and_increment('0');
        while (count < flags[5])
            count += write_and_increment(' ');
    }
    else if (flags[6] == 1)
    {
        write(1, "0.", 2);
        count += 2;
        while (flags[7]--)
            count += write_and_increment('0');
        while (count < flags[5])
            count += write_and_increment(' ');
    }
    return (count);
}

int     format_f_zero_right(int flags[], int count)
{
    if (flags[6] == 0) // precision not specified so automatically given to be 6
    {
        while (count < flags[5] - 8)
            count += (flags[3] == 1) ? write_and_increment('0') : write_and_increment(' '); 
        write(1, "0.000000", 8);
        count += 8;
    }
    else if (flags[6] == 1 && flags[7] == 0)
    {
        while (count < flags[5] - 1)
            count += write_and_increment(' ');
        count += write_and_increment('0');
    }
    else if (flags[6] == 1)
    {
        while (count < flags[5] - (2 + flags[7]))
            count += write_and_increment(' ');
        write(1, "0.", 1);
        count += 2;
        while (flags[7]--)
            count += write_and_increment('0');
    }
    return (count);
}
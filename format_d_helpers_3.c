/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_d_helpers_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 14:51:48 by mqian             #+#    #+#             */
/*   Updated: 2019/07/24 20:38:45 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     d_right_helper_1(int flags[], int arg_len, intmax_t argument, int count)
{
    if (flags[5] > flags[7]) //minw greater than precision
    {
        if (flags[7] > arg_len) //precision is greater than arg_len
            count += d_right_helper_3(flags, arg_len, argument, count);
        else //flags[7] <= arg_len, precision is less than or equal to arg_len so ignore
        {
            if (arg_len > flags[5])
                count += d_right_helper_4(flags, arg_len, argument, count);
            else //arg_len <= minw (flags[5]) precision ignored
                count += d_right_helper_5(flags, arg_len, argument, count);
        }
    }
    else //minw flags[5] <= precision flags[7]
        count += d_right_helper_6(flags, arg_len, argument, count);
    return (count);
}

int     d_right_helper_2(int flags[], int arg_len, intmax_t argument, int count)
{
    if (flags[5] > flags[7]) //minw greater than precision
    {
        if (flags[7] > arg_len)
            count += d_right_helper_7(flags, arg_len, argument, count);
        else // arg_len >= precision (flags[7])
            count += d_right_helper_8(flags, arg_len, argument, count);
    }
    else // minw <= than precision (flags[5] <= flags[7]) essentially left justified
        count += d_right_helper_9(flags, arg_len, argument, count);
    return (count);
}

int     d_right_helper_8(int flags[], int arg_len, intmax_t argument, int count)
{
    printf("in d_right_helper_8\n");
    if (arg_len > flags[5])
    {
        ft_putnbr(argument);
        count += arg_len;
        if (argument < 0)
            count++;
    }
    else
    {
        printf("went here instead\n");
        //printf("value of flags[3] == %d\n", flags[3]);
        // this portion of code below is identical to d_right_helper_5, so maybe just use that?
        if (flags[6] == 0 && flags[3] == 1) //minw > arg_len > precision
        {
            if (argument < 0)
            {
                count += write_and_increment('-');
                argument *= -1;
            }
            while (count < flags[5] - arg_len)
                count += write_and_increment('0');
        }
        else if (flags[6] == 1 || flags[3] == 0)
        {
            while (count < flags[5] - arg_len - 1)
                count += write_and_increment(' ');
            if (argument < 0)
            {
                count += write_and_increment('-');
                argument *= -1;
            }
            else
                count += write_and_increment(' ');
        }
        ft_putnbr(argument);
        count += arg_len;
    }
    return (count);
}

int     d_right_helper_9(int flags[], int arg_len, intmax_t argument, int count)
{
    if (argument < 0)
        write(1, "-", 1);
    if (flags[7] > arg_len) //precision greater than arg_len, need to pad with 0s
    {
        while (count < flags[7] - arg_len)
            count += write_and_increment('0');
        if (argument < 0)
        {
            count++;
            argument *= -1;
        }
        ft_putnbr(argument);
        count += arg_len;
    }
    else //arg_len >= flags[7], arg_len >precision >= flags[5], so print prepension and then just print the number since its right justified.
    {
        if (argument < 0)
        {
            count++;
            argument *= -1;
        }
        ft_putnbr(argument);
        count += arg_len;
    }
    return (count);
}
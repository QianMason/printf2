/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_u_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 14:53:50 by mqian             #+#    #+#             */
/*   Updated: 2019/07/30 15:22:12 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     format_u_left(int flags[], uintmax_t argument, int len)
{
    int count;

    count = 0;
    if (len >= flags[5] && len >= flags[7])
        count += print_uint_max(argument, 1);
    else if (flags[7] >= flags[5] && flags[7] >= len)
        count += format_u_left_helper_1(flags, dec, len);
    else if (flags[5] >= len && flags[5] >= flags[7])
    {
        if (len >= flags[7])
            count += format_u_left_helper_2(flags, dec, len);
        else // minw >= precision > len
            count += format_u_left_helper_3(flags, dec, len);
    }
    return (count);
}

int     format_u_left_helper_1(int flags[], uintmax_t argument, int len)
{
    int count;

    count = 0;
    while (count < flags[7] - len)
        count += write_and_increment('0');
    count += print_uint_max(argument, 1);
    return (count);
}

int     format_u_left_helper_2(int flags[], uintmax_t argument, int len)
{
    int count;

    count = 0;
    count += print_uint_max(argument, 1);
    while (count < flags[5])
        count += write_and_increment(' ');
    return (count);
}

int     format_u_left_helper_3(int flags[], uintmax_t argument, int len)
{
    int count;

    count = 0;
    while (count < flags[7] - len)
        count += write_and_increment('0');
    count += print_uint_max(argument, 1);
    while (count < flags[5])
        count += write_and_increment(' ');
    return (count);
}
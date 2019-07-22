/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_p_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 14:03:54 by mqian             #+#    #+#             */
/*   Updated: 2019/07/22 14:13:28 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     format_p_left_helper(int flags[], unsigned dec)
{
    int count;

    count = 0;
    write(1, "0x", 2);
    count += 2;
    if (flags[5] > 0) //minw
    {
        count += convert_to_hex(dec, 1);
        while (count < flags[5])
        {
            write(1, " ", 1);
            count++;
        }
    }
    else
        count += convert_to_hex(dec, 1); 
    return (count);
}

int     format_p_right_helper(int flags[], unsigned dec, int len)
{
    int count;

    count = 0;
    if (len + 2 > flags[5]) //since 0x
    {
        write(1, "0x", 2);
        count +=2;
        count += convert_to_hex(dec, 1);
    }
    else
    {
        while (count < (flags[5] - (len + 2)))
        {
            write(1, " ", 1);
            count++;
        }
        write(1, "0x", 2);
        count += 2;
        count += convert_to_hex(dec, 1);
    }
    return (count);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Thunderpurtz <Thunderpurtz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:25:03 by mqian             #+#    #+#             */
/*   Updated: 2019/07/22 21:52:39 by Thunderpurt      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int    convert_to_hex(unsigned n, int flag)
{
    unsigned temp;
    char c;
    int count;

    if (!n)
        return (0);
    temp = n % 16;
    if (temp < 10)
        c = temp + 48;
    else
        c = temp + 87;
    count = convert_to_hex(n/16, flag);
    if (flag == 1)
        write(1, &c, 1);
    count++;
    return (count);
}

int     get_int_length(unsigned n)
{
    int count;

    count = 0;
    while (n)
    {
        n /= 10;
        count++;
    }
    return (n);
}

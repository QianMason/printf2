/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:25:03 by mqian             #+#    #+#             */
/*   Updated: 2019/07/23 14:52:52 by mqian            ###   ########.fr       */
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

void    write_and_increment(char c)
{
    write(1, &c, 1);
    return (1);
}

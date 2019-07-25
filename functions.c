/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:25:03 by mqian             #+#    #+#             */
/*   Updated: 2019/07/24 20:22:45 by mqian            ###   ########.fr       */
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

int     get_int_len(intmax_t n)
{
    int count;

    count = 0;
    while (n)
    {
        n /= 10;
        count++;
    }
    return (count);
}

int     write_and_increment(char c)
{
    write(1, &c, 1);
    return (1);
}

intmax_t    get_int_arg(int flags[], va_list args)
{
    intmax_t argument;
    
    if (flags[8] == 1)
        argument = va_arg(args, signed char);
    else if (flags[8] == 2)
        argument = va_arg(args, short);
    else if (flags[8] == 3)
        argument = va_arg(args, long);
    else if (flags[8] == 4)
        argument = va_arg(args, long long);
    else
        argument = va_arg(args, int);
    return (argument);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:25:03 by mqian             #+#    #+#             */
/*   Updated: 2019/08/01 14:55:10 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int    convert_to_hex(uintmax_t n, int flag)
{
    uintmax_t temp;
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

int    convert_to_hex_upper(uintmax_t n, int flag)
{
    uintmax_t temp;
    char c;
    int count;

    if (!n)
        return (0);
    temp = n % 16;
    if (temp < 10)
        c = temp + 48;
    else
        c = temp + 55;
    count = convert_to_hex_upper(n/16, flag);
    if (flag == 1)
        write(1, &c, 1);
    count++;
    return (count);
}

int     convert_to_octal(uintmax_t n, int flag)
{
    uintmax_t temp;
    char c;
    int count;
    if (!n)
        return (0);
    temp = n % 8;
    c = temp + 48;
    count = convert_to_octal(n / 8, flag);
    if (flag == 1)
        write(1, &c, 1);
    count++;
    return (count);
}

int     print_uint_max(uintmax_t n, int flag)
{
    uintmax_t temp;
    char c;
    int count;
    if (!n)
        return (0);
    temp = n % 10;
    c = temp + 48;
    count = print_uint_max(n / 10, flag);
    if (flag == 1)
        write(1, &c, 1);
    count++;
    return (count);
}

int     get_int_len(intmax_t n)
{
    int count;

    count = 0;
    if (n == 0)
        return (1);
    while (n)
    {
        n /= 10;
        count++;
    }
    return (count);
}

int     get_uint_len(uintmax_t n)
{
    int count;

    count = 0;
    if (n == 0)
        return (1);
    while (n)
    {
        n /= 10;
        count++;
    }
    return (count);
}

int     write_and_increment(wint_t c)
{
    write(1, &c, 1);
    return (1);
}

intmax_t    get_int_arg(int flags[], va_list args)
{
    intmax_t argument;
    
    if (flags[8] == 1)
        argument = va_arg(args, signed char); //need to promote?
    else if (flags[8] == 2)
        argument = va_arg(args, int);
    else if (flags[8] == 3)
        argument = va_arg(args, long);
    else if (flags[8] == 4)
        argument = va_arg(args, long long);
    else
        argument = va_arg(args, int);
    return (argument);
}

int     not_valid_format(char c)
{
    if (c > 57 || c < 48)
        return (1); //invalid
    return (0);
}

// wint_t  get_char_arg(int flags[], va_list args)
// {
//     wint_t c;

//     if (flags[8] == 'l')
//         c = va_arg(args, wint_t);
//     else
//         c = va_arg(args, unsigned char);
//     return (c);
// }
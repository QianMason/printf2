/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 11:57:31 by mqian             #+#    #+#             */
/*   Updated: 2019/08/19 15:07:34 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     convert_to_hex(uintmax_t n, int flag)
{
    uintmax_t	temp;
    char		c;
    int			count;

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

int     convert_to_hex_upper(uintmax_t n, int flag)
{
    uintmax_t	temp;
    char		c;
    int			count;

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
    uintmax_t	temp;
    char		c;
    int			count;
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

int     print_uint_max(uintmax_t n, int flag, int level)
{
    uintmax_t	temp;
    char		c;
    int			count;
    if (!n && level == 0)
    {
        write(1, "0", 1);
        return (1);
    }
    else if (!n)
        return (0);
    temp = n % 10;
    c = temp + 48;
    count = print_uint_max(n / 10, flag, level + 1);
    if (flag == 1)
        write(1, &c, 1);
    count++;
    return (count);
}

int     print_float(intmax_t hold, int prec, int dot)
{
    int			count;
    intmax_t	temp;
    char		c;
    
    count = 0;
    if (!hold)
        return (0);
    temp = hold % 10;
    c = temp + 48;
    count = print_float(hold / 10, prec, dot + 1);
    write(1, &c, 1);
    count++;
    if (dot == prec)
    {
        write(1, ".", 1);
        count++;
    }
    return (count);
}

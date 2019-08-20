/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:25:03 by mqian             #+#    #+#             */
/*   Updated: 2019/08/19 16:19:39 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				get_int_len(intmax_t n)
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

int				get_uint_len(uintmax_t n)
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

int				write_and_increment(wint_t c)
{
    write(1, &c, 1);
    return (1);
}

intmax_t		get_int_arg(int flags[], va_list args)
{
    intmax_t argument;

    if (flags[8] == 1)
        argument = va_arg(args, int); //need to promote?
    else if (flags[8] == 2) //short
        argument = (short)va_arg(args, int);
    else if (flags[8] == 3)
        argument = va_arg(args, long);
    else if (flags[8] == 4)
        argument = va_arg(args, long long);
    else
        argument = va_arg(args, int);
    return (argument);
}

long double		get_float_arg(int flags[], va_list args)
{
    if (flags[8] == 5) //'L' flag shown
        return (va_arg(args, long double));
    return (va_arg(args, double));
}
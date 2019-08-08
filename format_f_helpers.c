/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_f_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:19:48 by Thunderpurt       #+#    #+#             */
/*   Updated: 2019/08/07 16:46:25 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     format_f_string(long double argument, char **f_string)
{
    int len;

    if (f_prec_default(flags) == 1)
        *f_string = build_f_string(argument, 6);
    else
        *f_string = build_f_string(argument, flags[7]);
    len = ft_strlen(*f_string);
    return (len);
}

char    *build_f_string(long double argument, int prec)
{
    char *f_string;
    intmax_t hold;
    int len;

    hold = (intmax_t)argument;
    len = get_int_len(hold) + prec + 1;
    f_string = ft_strnew(len); //len of front part, prec, .
    ft_bzero((void *)temp, len + 1);
    build_float(hold, prec, len, f_string);
    return (f_string);
}

int     f_prec_default(int flags[])
{
    if (flags[6] == 0 || (flags[6] == 1 && flags[7] == 0))
        return (1);
    return (0);
}

void    build_float(intmax_t hold, int prec, int len, char *f_string)
{
    char c;
    intmax_t temp;
    int index;

    index = len;
    if (hold < 0)
        hold *= -1;
    while (--index >= 0)
    {
        if (index == len - prec - 1)
        {
            f_string[index] = '.';
            continue;
        }
        temp = hold % 10;
        c = temp + 48;
        f_string[index] = c;
        hold /= 10;
    }
}
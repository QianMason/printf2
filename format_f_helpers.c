/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_f_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:19:48 by Thunderpurt       #+#    #+#             */
/*   Updated: 2019/08/12 15:14:50 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     format_f_string(int flags[], long double argument, char **f_string)
{
    int len;

    if (flags[6] == 0)
        *f_string = build_f_string(argument, 6);
    else if (flags[6] == 1 && flags[7] == 0)
        *f_string = build_f_string(argument, 0);
    else
        *f_string = build_f_string(argument, flags[7]);
    printf("fstring: %s\n", *f_string);
    len = ft_strlen(*f_string);
    return (len);
}

char    *build_f_string(long double argument, int prec)
{
    char *f_string;
    intmax_t hold;
    int len;

    hold = (intmax_t)argument;
    len = (prec > 0) ? get_int_len(hold) + prec + 1 : get_int_len(hold);
    f_string = ft_strnew(len); //len of front part, prec, .
    ft_bzero((void *)f_string, len + 1);
    hold = get_prec_num_f(argument, prec);
    build_float(hold, prec, len, f_string);
    return (f_string);
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
        if (index == len - prec - 1 && prec > 0)
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_c_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 13:00:01 by mqian             #+#    #+#             */
/*   Updated: 2019/08/19 12:46:05 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		format_c_left(int flags[], wint_t argument)
{
    int count;

    count = 0;
    count += write_and_increment(argument);
    while (count < flags[5])
        count += write_and_increment(' ');
    return (count);
}

int		format_c_right(int flags[], wint_t argument)
{
    int count;

    count = 0;
    while (count < flags[5] - 1)
        count += write_and_increment(' ');
    count += write_and_increment(argument);
    return (count);
}
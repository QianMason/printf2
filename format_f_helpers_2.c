/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_f_helpers_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:49:48 by mqian             #+#    #+#             */
/*   Updated: 2019/08/06 17:18:34 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int     format_f_right(int flags[], intmax_t hold, int len)
{
    int count;

    count = 0;
    if (flags[3] == 1 && flags[6] == 0)
    {
        count += format_d_sign(flags, &hold);
        while (count < flags[5] - len)
            count += write_and_increment('0');
        count += print_float(hold, 6, 0);
    }
    else if (flags[6] == 1 && flags[7] == 0)
    {
        while (count < flags[5] - len - 1)
            count += write_and_increment(' ');
        count += format_d_sign(flags, &hold);
        count += print_uint_max(hold, 1);
    }
    else
    {
        while (count < flags[5] - len - 1)
            count += write_and_increment(' ');
        count += format_d_sign(flags, &hold);
        count += (flags[6] == 0) ? print_float(hold, 6, 0) : print_float(hold, flags[7], 0);
    }
    return (count);
}
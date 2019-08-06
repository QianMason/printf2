/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_f_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:19:48 by Thunderpurt       #+#    #+#             */
/*   Updated: 2019/08/05 18:51:48 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int     format_f_left(int flags[], intmax_t hold, int len)
{
    int count;

    count = 0;
    if (hold == 0)
        return (format_f_zero(flags, hold));
    count = format_d_sign(flags, hold);
    count += print_float(hold, flags[7], 0);
    while (count < flags[5])
        count += write_and_increment(' ');
    return (count);
}

// int     format_f_left_helper_1(int flags[], intmax_t hold)
// {
//     int count;

//     count = 0;
//     if (hold == 0)
//         return (format_f_zero(flags, hold));
//     count = format_d_sign(flags, hold);
//     count += print_float(hold, flags[7], 0);
    
//     return (count);
// }

// int     format_f_left_helper_2(int flags[], intmax_t hold, int len)
// {

// }

int     format_f_zero(int flags[], intmax_t hold)
{
    int count;

    count = 0;
    count += write_and_increment('0');
    if (flags[6] == 1 && flags[7] == 0)
    {
        while (count < flags[5])
            count += write_and_increment(' ');
    }
    else if (flags[6] == 1)//now consider if theres regular precision and no precision at all
    {
        count += write_and_increment('.');
        while (flags[7]-- > 0)
            count += write_and_increment('0');
        while (count < flags[5])
            count += write_and_increment(' ');
    }
    else //precision automatically 6
    {
        write(1, ".000000", 7);
        count += 7;
        while (count < flags[5])
            count += write_and_increment(' ');
    }
    return (count);
}
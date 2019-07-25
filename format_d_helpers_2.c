/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_d_helpers_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 14:21:17 by mqian             #+#    #+#             */
/*   Updated: 2019/07/25 16:38:04 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		d_right_helper_3(int flags[], int arg_len, intmax_t argument, int count)
{
	while (count < flags[5] - flags[7] - 1)
		count += write_and_increment(' ');
	if (argument == 0)
		count += write_and_increment(' ');
	else if (argument < 0)
	{
		count += write_and_increment('-');
		argument *= -1;
	}
	else
		count += write_and_increment('+');
	while (count < flags[5] - arg_len)
		count += write_and_increment('0');
	ft_putnbr(argument);
	count += arg_len;
	return (count);
}

int		d_right_helper_4(int flags[], int arg_len, intmax_t argument, int count)
{
	if (argument == 0)
	{
		ft_putnbr(argument);
		count++;
	}
	else if (argument < 0)
	{
		count += write_and_increment('-');
		argument *= -1;
	}
	else
		count += write_and_increment('+');
	ft_putnbr(argument);
	count += arg_len;
	return (count);
}

int		d_right_helper_5(int flags[], int arg_len, intmax_t argument, int count)
{
    if (flags[6] == 0 && flags[3] == 1) //minw > arg_len > precision
    {
        if (argument < 0)
        {
            count += write_and_increment('-');
            argument *= -1;
        }
        else if (argument > 0)
            count += write_and_increment('+');
        while (count < flags[5] - arg_len)
            count += write_and_increment('0');
    }
    else if (flags[6] == 1 || flags[3] == 0)
    {
        while (count < flags[5] - arg_len - 1)
            count += write_and_increment(' ');
        if (argument < 0)
        {
            count += write_and_increment('-');
            argument *= -1;
        }
        else if (argument > 0)
            count += write_and_increment('+');
        else
            count += write_and_increment(' ');
    }
    ft_putnbr(argument);
    count += arg_len;
	return (count);
}



int     d_right_helper_6(int flags[], int arg_len, intmax_t argument, int count)
{
    if (argument > 0)
        write(1, "+", 1);
    else if (argument < 0)
    {
        write(1, "-", 1);
        argument *= -1;
    }
    if (flags[7] > arg_len)
    {
        while (count < flags[7] - arg_len)
            count += write_and_increment('0');
    }
    ft_putnbr(argument);
    count += arg_len;
    if (argument != 0)
        count++;
    return (count);
}

int     d_right_helper_7(int flags[], int arg_len, intmax_t argument, int count)
{
    while (count < flags[5] - flags[7] - 1)
        count += write_and_increment(' ');
    if (argument < 0)
    {
        count += write_and_increment('-');
        argument *= -1;
    }
    while (count < flags[5] - arg_len)
        count += write_and_increment('0');
    ft_putnbr(argument);
    count += arg_len;
    return (count);
}
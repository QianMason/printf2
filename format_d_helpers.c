/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_d_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 21:36:29 by Thunderpurt       #+#    #+#             */
/*   Updated: 2019/07/23 16:22:15 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		format_d_left(int flags[], int argument) //left align
{
	int count;
	int arg_len;

	count = 0;
	arg_len = get_int_len(argument);
	if (flags[0] == 1) // '+' seen which means prepend a + or - based on if the number is positive or negative
	{
		if (argument < 0)
		{
			count += write_and_increment('-');
			argument *= -1; //convert to positive
		}
		else if (argument > 0)
			count += write_and_increment('+');
		if (flags[7] > arg_len)
		{
			while (count < flags[7] - arg_len)
				count += write_and_increment('0');
			ft_putnbr(argument);
			count += arg_len;
			while (count < flags[5])
				count += write_and_increment(' ');
		}
		else //precision is less than argument length or is zero
		{
			ft_putnbr(argument);
			count += arg_len;
			while (count < flags[5])
				count += write_and_increment(' ');
		}
	}
	else //flags[0] == 0 so no prepended + or - so 0 flag is not overrided
	{
		if (argument < 0)
		{
			count += write_and_increment('-');
			argument *= -1; //convert to positive
		}
		if (flags[7] > arg_len)
		{
			while (count < flags[6] - arg_len)
				count += write_and_increment('0');
			ft_putnbr(argument);
			count += arg_len;
			while (count < flags[5])
				count += write_and_increment(' ');
		}
		else //precision is less than argument length or is zero/not present
		{
			ft_putnbr(argument);
			count += arg_len;
			while (count < flags[5] && flags[3] == 0) //precision is ignored so print ' 's if the 0 flag is not present
				count += write_and_increment(' ');
			while (count < flags[5] && flags[3] == 1) //precision is ignored so print '0's if the 0 flag is present
				count += write_and_increment('0');
		}
	}
	return (count);
}

int		format_d_right(int flags[], int argument)
{
	int count;
	int arg_len;

	count = 0;
	arg_len = get_int_len(argument);
	if (flags[0] == 1) // prepend a + or - based on argument sign
	{
		if (flags[6] > arg_len)
		{
			while (count < flags[6] - arg_len)
			{
				write(1, ' ', 1);
				count++;
			}
			if (argument < 0)
			{
				write(1, "-", 1);
				count++;
				argument *= -1;
			}
			else if (argument > 0)
			{
				write(1, "+", 1);
				count++;
			}
		}
	}
}
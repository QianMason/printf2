/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_d_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 21:36:29 by Thunderpurt       #+#    #+#             */
/*   Updated: 2019/07/23 15:19:14 by mqian            ###   ########.fr       */
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
		if (argument < 0) //left align, where there is a prepended + and the number is less than 0
		{
			count += write_and_increment('-');
			if (flags[6] > arg_len)
			{
				while (count < flags[6] - arg_len)
				{
					if (flags[3] == 1) //0 flag present, prepend 0's
						count += write_and_increment('0');
					else
						count += write_and_increment(' ');
				}
			}
		}
	}
}

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
			write(1, "-", 1);
			count++;
			argument *= -1; //convert to positive
		}
		else if (argument > 0)
		{
			write(1, "+", 1);
			count++;
		}
		if (flags[6] > arg_len)
		{
			while (count < flags[6] - arg_len)
			{
				write(1, "0", 1);
				count++;
			}
			ft_putnbr(argument);
			count += arg_len;
			while (count < flags[5])
			{
				write(1, " ", 1);
				count++;
			}
		}
		else //precision is less than argument length or is zero
		{
			ft_putnbr(argument);
			count += arg_len;
			while (count < flags[5])
			{
				write(1, " ", 1);
				count++;
			}
		}
	}
	else //flags[0] == 0 so no prepended + or -
	{
		if (argument < 0)
		{
			write(1, "-", 1);
			count++;
			argument *= -1;
		}
		if (flags[6] > arg_len)
		{
			while (count < flags[6] - arg_len)
			{
				write(1, "0", 1);
				count++;
			}
			ft_putnbr(argument);
			count += arg_len;
			while (count < flags[5])
			{
				write(1, " ", 1);
				count++;
			}
		}
		else
		{
			ft_putnbr(argument);
			count += arg_len;
			while (count < flags[5])
			{
				write(1, " ", 1);
				count++;
			}
		}
	}
	return (count);
}
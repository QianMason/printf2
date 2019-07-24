/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_d_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 21:36:29 by Thunderpurt       #+#    #+#             */
/*   Updated: 2019/07/23 18:22:54 by mqian            ###   ########.fr       */
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
			while (count < flags[7] - arg_len)
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
		if (flags[5] > flags[7]) //minw greater than precision
		{
			if (flags[7] > arg_len) //precision is greater than arg_len
			{
				if (argument == 0)
				{
					while (count < flags[5] - flags[7])
						count += write_and_increment(' ');
				}
				else if (argument < 0)
				{
					while (count < flags[5] - flags[7] - 1)
						count += write_and_increment(' ');
					count += write_and_increment('-');
					argument *= -1;
				}
				else if (argument > 0)
				{
					while (count < flags[5] - flags[7] - 1)
						count += write_and_increment(' ');
					count += write_and_increment('+');
				}
				while (count < flags[5] - arg_len)
					count += write_and_increment('0');
				ft_putnbr(argument);
				count += arg_len;
			}
			else //flags[7] <= arg_len, precision is less than or equal to arg_len so ignore
			{
				if (arg_len > flags[5])
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
				}
				else //arg_len <= minw (flags[5]) precision ignored
				{
					if (flags[3] == 1)
					{
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
					}
					else
					{
						while (count < flags[5] - arg_len - 1)
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
					}
					ft_putnbr(argument);
					count += arg_len;
				}
			}
		}
		else //minw flags[5] <= precision flags[7]
		{
			if (argument > 0)
			{
				count += write_and_increment('+');
				flags[7]++;
			}
			else if (argument < 0)
			{
				count += write_and_increment('-');
				flags[7]++;
				argument *= -1;
			}
			if (flags[7] - 1 > arg_len) //precision greater than arg_len, need to pad with 0s
			{
				while (count < flags[7] - arg_len)
					count += write_and_increment('0');
				ft_putnbr(argument);
				count += arg_len;
			}
			else //arg_len >= flags[7], arg_len >precision >= flags[5], so print prepension and then just print the number since its right justified.
			{
				ft_putnbr(argument);
				count += arg_len;
			}
		}
	}
	else //no +/- prepensions
	{
		if (flags[5] > flags[7]) //minw greater than precision
		{
			if (flags[7] > arg_len)
			{
				while (count < flags[5] - flags[7] - 1)
				{
					if (flags[3] == 1)
						count += write_and_increment('0');
					else
						count += write_and_increment(' ');
				}
				if (argument < 0)
				{
					count += write_and_increment('-');
					argument *= -1;
				}
				while (count < flags[5] - arg_len) //write zeros til the argument
					count += write_and_increment('0');
				ft_putnbr(argument);
				count += arg_len;
			}
			else // arg_len >= precision (flags[7])
			{
				if (arg_len > flags[5])
				{
					if (argument < 0)
					{
						count += write_and_increment('-');
						argument *= -1;
					}
					ft_putnbr(argument);
					count += arg_len;
				}
				else // arg_len <= minw (flags[5]) precision ignored
				{
					while (count < flags[5] - arg_len - 1)
					{
						if (flags[3] == 1)
							count += write_and_increment('0');
						else
							count += write_and_increment(' ');
					}
					if (argument < 0)
					{
						count += write_and_increment('-');
						argument *= -1;
					}
					else
						count += write_and_increment(' ');
					ft_putnbr(argument);
					count += arg_len;
				}
			}
		}
		else // minw less than precision (flags[5] <= flags[7]) essentially left justified
		{
			if (argument < 0)
			{
				count += write_and_increment('-');
				flags[7]++;
				argument *= -1;
			}
			if (flags[7] - 1 > arg_len) //precision greater than arg_len, need to pad with 0s
			{
				while (count < flags[7] - arg_len)
					count += write_and_increment('0');
				ft_putnbr(argument);
				count += arg_len;
			}
			else //arg_len >= flags[7], arg_len >precision >= flags[5], so print prepension and then just print the number since its right justified.
			{
				ft_putnbr(argument);
				count += arg_len;
			}
		}
	}
	return (count);
}
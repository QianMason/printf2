/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_d_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 21:36:29 by Thunderpurt       #+#    #+#             */
/*   Updated: 2019/07/24 20:40:51 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		format_d_left(int flags[], intmax_t argument) //left align
{
	int count;
	int arg_len;

	count = 0;
	arg_len = get_int_len(argument);
	if (flags[0] == 1) // '+' seen which means prepend a + or - based on if the number is positive or negative
		count += format_d_left_helper_1(flags, arg_len, argument, count);
	else //flags[0] == 0 so no prepended + or - so 0 flag is not overrided
		count += format_d_left_helper_2(flags, arg_len, argument, count);
	return (count);
}


int		format_d_left_helper_1(int flags[], int arg_len, intmax_t argument, int count)
{
    intmax_t orig;
    
    orig = argument;
	if (argument < 0)
	{
		write(1, "-", 1);
		argument *= -1; //convert to positive
	}
	else if (argument > 0)
		write(1, "+", 1);
	count += format_d_left_helper_4(flags, arg_len, argument, orig);
	return (count);
}

int		format_d_left_helper_2(int flags[], int arg_len, intmax_t argument, int count)
{
	intmax_t orig;

	orig = argument;
	if (argument < 0)
	{
		write(1, "-", 1);
		argument *= -1; //convert to positive
	}
	count += format_d_left_helper_3(flags, arg_len, argument, orig);
	return (count);
}

int		format_d_left_helper_3(int flags[], int arg_len, intmax_t argument, intmax_t orig)
{
	int count;

	count = 0;
	if (flags[7] > arg_len)
	{
		while (count < flags[7] - arg_len)
			count += write_and_increment('0');
		ft_putnbr(argument);
		count += (orig < 0) ? arg_len + 1: arg_len; //need to update count here to handle tis condition
		while (count < flags[5])
			count += write_and_increment(' ');
	}
	else //precision is less than argument length or is zero/not present
	{
		ft_putnbr(argument);
		count += (orig < 0) ? arg_len + 1: arg_len;
		while (count < flags[5] && (flags[3] == 0 || flags[6] == 1)) //precision is ignored so print ' 's if the 0 flag is not present
			count += write_and_increment(' ');
		while (count < flags[5] && flags[3] == 1 && flags[6] == 0) //precision is ignored so print '0's if the 0 flag is present
			count += write_and_increment('0');
	}
	return (count);
}


int		format_d_left_helper_4(int flags[], int arg_len, intmax_t argument, intmax_t orig)
{
	int count;

	count = 0;
	if (flags[7] > arg_len)
	{
		while (count < flags[7] - arg_len)
			count += write_and_increment('0');
		ft_putnbr(argument);
		count += (orig != 0) ? arg_len + 1: arg_len;
		while (count < flags[5])
			count += write_and_increment(' ');
	}
	else //precision is less than argument length or is zero
	{
		ft_putnbr(argument);
		count += (orig != 0) ? arg_len + 1: arg_len;
		while (count < flags[5])
			count += write_and_increment(' ');
	}
	return (count);
}

int		format_d_right(int flags[], intmax_t argument)
{
	int count;
	int arg_len;

	count = 0;
	arg_len = get_int_len(argument);
	//printf("argument: %d, argument length: %d\n", argument, arg_len);
	if (flags[0] == 1) // prepend a + or - based on argument sign
		count += d_right_helper_1(flags, arg_len, argument, count);
	else //no +/- prepensions
		count += d_right_helper_2(flags, arg_len, argument, count);
	return (count);
}
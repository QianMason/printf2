/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_d_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Thunderpurtz <Thunderpurtz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 21:36:29 by Thunderpurt       #+#    #+#             */
/*   Updated: 2019/07/22 22:58:09 by Thunderpurt      ###   ########.fr       */
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
			write(1, "-", 1);
			count++;
			if (flags[6] > arg_len)
			{
				while (count < flags[6] - arg_len)
				{
					if (flags[3] == 1) //0 flag present, prepend 0's
					{
						write(1, "0", 1);
						count++;
					}
					else
					{
						write(1, " ", 1);
						count++;
					}
				}
			}
		}
	}
}

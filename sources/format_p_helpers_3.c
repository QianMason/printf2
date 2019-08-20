/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_p_helpers_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:04:33 by mqian             #+#    #+#             */
/*   Updated: 2019/08/20 14:29:21 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		format_p_zero(int flags[])
{
	int count;

	count = 0;
	if (flags[1] == 1)
		count += format_p_zero_left(flags, count);
	else
		count += format_p_zero_right(flags, count);
	return (count);
}

int		format_p_zero_left(int flags[], int count)
{
	int temp;

	temp = 0;
	write(1, "0x", 2);
	count += 2;
	while (temp++ < flags[7])
		count += write_and_increment('0');
	while (count < flags[5])
		count += write_and_increment(' ');
	return (count);
}

int		format_p_zero_right(int flags[], int count)
{
	int temp;

	temp = 0;
	while (count < flags[5] - flags[7] - 2)
		count += write_and_increment(' ');
	write(1, "0x", 2);
	count += 2;
	while (temp++ < flags[7])
		count += write_and_increment('0');
	return (0);
}

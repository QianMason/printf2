/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 17:06:44 by mqian             #+#    #+#             */
/*   Updated: 2019/08/19 17:28:52 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uintmax_t	get_x_int_arg(int flags[], va_list args)
{
	intmax_t argument;
	if (flags[8] == 1)
		argument = va_arg(args, int);
	else if (flags[8] == 2)
		argument = (short)va_arg(args, int);
	else if (flags[8] == 3)
		argument = (unsigned long)va_arg(args, long);
	else if (flags[8] == 4)
		argument = (unsigned long long)va_arg(args, long long);
	else
		argument = (unsigned int)va_arg(args, int);
	return (argument);
}


int		print_int_max(intmax_t n, int flag)
{
	intmax_t	temp;
	char		c;
	int			count;

	if (!n)
		return (0);
	temp = n % 10;
	c = temp + 48;
	count = print_int_max(n / 10, flag);
	if (flag == 1)
		write(1, &c, 1);
	count++;
	return (count);
}

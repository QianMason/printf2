/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatters1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 14:21:42 by Thunderpurt       #+#    #+#             */
/*   Updated: 2019/08/19 14:58:45 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		format_c(int flags[], va_list args)
{
    int		count;
    wint_t	c;

    c = va_arg(args, wint_t);
    if (flags[1] == 1)
        count = format_c_left(flags, c);
    else
        count = format_c_right(flags, c);
    return (count);
}

int		format_d(int flags[], va_list args)
{
	int			count;
	intmax_t	argument;
	int			len;

	count = 0;
	argument = get_int_arg(flags, args);
	len = get_int_len(argument);
	if (flags[1] == 1) //left align
		count = format_d_left(flags, argument, len);
	else
		count = format_d_right(flags, argument, len);
	return (count);
}

int		format_f(int flags[], va_list args)
{
	int			count;
	int			len;
	long double argument;
	char 		*temp;

	argument = get_float_arg(flags, args);
	count = 0;
	if (argument == 0 || f_test_zero(flags, argument) == 0) //0 case or truncated string would round to zero
		return (format_f_zero(flags, argument));
	if ((argument < 1 && argument > 0) || (argument < 0 && argument > -1)) //self explanatory
		return (format_f_special(flags, argument, count));
	len = format_f_string(flags, argument, &temp); //sets up temp string, returns length of created string
    if (flags[1] == 1)
		count += format_f_left(flags, temp, argument);
	else
		count += format_f_right(flags, temp, len, argument);
	free(temp);
	return (count);
}


int		format_i(int flags[], va_list args)
{
	return(format_d(flags, args));
}

int		format_o(int flags[], va_list args)
{
	int			count;
	uintmax_t	argument;
	int			len;

	count = 0;
	argument = (uintmax_t)get_int_arg(flags, args); //this might give you issues
	len = (argument > 0) ? convert_to_octal(argument, 0) : 1;
	if (flags[1] == 1) //left align
		count = format_o_left(flags, argument, len);
	else
		count = format_o_right(flags, argument, len);
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatters1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 14:21:42 by Thunderpurt       #+#    #+#             */
/*   Updated: 2019/08/05 18:45:40 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     format_c(int flags[], va_list args)
{
    int count;
    wint_t c;

    c = va_arg(args, wint_t);
    if (flags[1] == 1)
        count = format_c_left(flags, c);
    else
        count = format_c_right(flags, c);
    return (count);
}

int		format_d(int flags[], va_list args)
{
	int count;
	intmax_t argument;
	int len;

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
	int count;
	int len;
	long double argument;
	intmax_t hold;

	argument = va_arg(args, long double);
	hold = (flags[6] > 0) ? get_prec_num_f(argument, flags[7]) : get_prec_num_f(argument, 6);
	if (flags[6] == 1 && flags[7] == 0) //precision specifically 0, so just get len of the rounded value
		len = (hold != 0) ? get_int_len((intmax_t)argument) : 1; //since we just want rounded, convert to intmax_t and add 1
	else //follow to limit of precision
	{
		if (hold != 0)
			len = get_int_len(hold) + 1;
		else // we have a 0, and now we want len of precision after 0
			len = (flags[6] == 0) ? 8 : flags[7] + 2; //prec not spec, so it 6 + 1 '.' + 1 '0' otherwise its prec + 2
	}	
	if (flags[1] == 1)
		count = format_f_left(flags, hold, len);
	else
		count = format_f_right(flags, hold, len);
	return (count);
}

int		format_i(int flags[], va_list args)
{
	return(format_d(flags, args));
}

int		format_o(int flags[], va_list args)
{
	int count;
	uintmax_t argument;
	int len;

	count = 0;
	argument = (uintmax_t)get_int_arg(flags, args); //this might give you issues
	len = (argument > 0) ? convert_to_octal(argument, 0) : 1;
	if (flags[1] == 1) //left align
		count = format_o_left(flags, argument, len);
	else
		count = format_o_right(flags, argument, len);
	return (count);
}

// void format_c(char *format)
// {
// 	printf("format string c: %s\n", format);
// 	return ;
// }

// void format_d(char *format)
// {
// 	printf("format string d: %s\n", format);
// 	return ;
// }

// void format_f(char *format)
// {
// 	printf("format string f: %s\n", format);
// 	return ;
// }

// void format_i(char *format)
// {
// 	printf("format string i: %s\n", format);
// 	return ;
// }

// void format_s(char *format)
// {
// 	printf("%s", format);
// 	return ;
// }

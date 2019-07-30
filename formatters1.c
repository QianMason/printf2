/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatters1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 14:21:42 by Thunderpurt       #+#    #+#             */
/*   Updated: 2019/07/30 16:46:10 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		format_c(int flags[], va_list args)
{
	int count;
	char c;

	count = 0;
	c = va_arg(args, int);
	if (flags[1] == 1) //left justify
	{
		count++;
		write(1, &c, 1);
		while (count < flags[5])
		{
			write(1, " ", 1);
			count++;
		}
	}
	else
	{
		while (count++ < flags[5] - 1)
			write(1, " ", 1);
		write(1, &c, 1);
		//count++; by doing it this way, the count++ on the top will account for the extra ++ needed on the bottom
	}
	return (count);
}

int		format_d(int flags[], va_list args)
{
	int count;
	intmax_t argument;

	count = 0;
	argument = get_int_arg(flags, args);
	if (flags[1] == 1) //left align
		count = format_d_left(flags, argument);
	else
		count = format_d_right(flags, argument);
	return (count);
}

int		format_f(int flags[], va_list args)
{
	printf("format string f: %s\n", print->format);
	return (0);
}

int		format_i(int flags[], va_list args)
{
	printf("format string i: %s\n", print->format);
	return (0);
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

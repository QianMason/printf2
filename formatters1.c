/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatters1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Thunderpurtz <Thunderpurtz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 14:21:42 by Thunderpurt       #+#    #+#             */
/*   Updated: 2019/07/22 21:53:26 by Thunderpurt      ###   ########.fr       */
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
	int argument;

	count = 0;
	argument = va_arg(args, int); //should i try unsigned?
	if (flags[1] == 1) //left align
		count = format_d_left_helper(flags, args);
	else
		count = format_d_right_helper(flags, args);

	printf("format string d: %s\n", print->format);
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
	printf("%s", print->format);
	return (0);
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

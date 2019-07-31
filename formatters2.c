/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatters2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 14:21:57 by Thunderpurt       #+#    #+#             */
/*   Updated: 2019/07/30 18:58:18 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

    // unsigned normal;
    // unsigned *pointer;
    // pointer = &normal;
    // normal = (unsigned)pointer;
int		format_p(int flags[], va_list args)
{
	int count;
	void *temp;
	uintmax_t dec;
	int len;

	count = 0;
	temp = va_arg(args, void*);
	dec = temp;
	len = convert_to_hex(dec, 0);
	if (!temp)
	{
		write(1, "0x0", 3);
		count += 3;
	}
	else if (flags[1] == 1) //left justify
		count += format_p_left(flags, dec, len);
	else //right justify
		count += format_p_right(flags, dec, len);
	return (count);
}

int		format_s(int flags[], va_list args) //first one you are working on
{
	int count;
	char *temp;
	char *len;

	temp = va_arg(args, char *);
	len = strlen(temp);
	if (!flags[5] && !flags[6])
	{
		write(1, temp, len);
		return (len);
	}
	else
	{
		if (flags[1] == 1)
		{
		    printf("format s left call\n");
		    count = format_s_left(flags, temp, len); //non default behavior
		}
		else
		{
		    printf("format s right call\n");
			count = format_s_right(flags, temp, len); //default behavior
		}
	}
	return (count);
}

int		format_u(int flags[], va_list args)
{
	int count;
	uintmax_t argument;
	int len;

	count = 0;
	argument = (uintmax_t)get_int_arg(flags, args); //this might give you issues
	len = get_uint_len(argument);
	if (flags[1] == 1) //left align
		count = format_u_left(flags, argument, len);
	else
		count = format_u_right(flags, argument, len);
	return (count);
}

int		format_x(int flags[], va_list args)
{
	int count;
	uintmax_t argument;
	int len;
	
	count = 0;
	argument = (uintmax_t)get_int_arg(flags, args);
	len = convert_to_hex(argument, 0);
	if (flags[1] == 1)
		count = format_x_left(flags, argument, len);
	else
		count = format_x_right(flags, argument, len);
	return (count);
}

int		format_x_upper(int flags[], va_list args)
{
	printf("format string X(upper): %s\n", print->format);
	return (0);
}

// void format_o(char *format)
// {
// 	printf("format string o: %s\n", format);
// 	return ;
// }

// void format_p(char *format)
// {
// 	printf("format string p: %s\n", format);
// 	return ;
// }

// void format_u(char *format)
// {
// 	printf("format string u: %s\n", format);
// 	return ;
// }

// void format_x(char *format)
// {
// 	printf("format string x: %s\n", format);
// 	return ;
// }

// void format_x_upper(char *format)
// {
// 	printf("format string X(upper): %s\n", format);
// 	return ;
// }

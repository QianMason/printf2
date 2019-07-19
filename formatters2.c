/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatters2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 14:21:57 by Thunderpurt       #+#    #+#             */
/*   Updated: 2019/07/19 15:58:00 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		format_p(int flags[], va_list args)
{
	printf("format string p: %s\n", print->format);
	return (0);
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
	printf("format string u: %s\n", print->format);
	return (0);
}

int		format_x(int flags[], va_list args)
{
	printf("format string x: %s\n", print->format);
	return (0);
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

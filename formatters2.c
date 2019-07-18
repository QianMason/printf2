/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatters2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 14:21:57 by Thunderpurt       #+#    #+#             */
/*   Updated: 2019/07/17 18:26:40 by mqian            ###   ########.fr       */
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
	int i;
	int len;
	char *temp;

	temp = va_arg(args, char *)
	len = ft_strlen(temp);
	while (print->)
	i = 0;

	printf("format string s: %s\n", print->format);
	return (0);
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

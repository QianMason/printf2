/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatters2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 14:21:57 by Thunderpurt       #+#    #+#             */
/*   Updated: 2019/07/17 16:39:35 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		format_p(t_print_struct *print, va_list args)
{
	printf("format string p: %s\n", print->format);
	return (0);
}

int		format_s(t_print_struct *print, va_list args)
{
	printf("format string s: %s\n", print->format);
	return (0);
}

int		format_u(t_print_struct *print, va_list args)
{
	printf("format string u: %s\n", print->format);
	return (0);
}

int		format_x(t_print_struct *print, va_list args)
{
	printf("format string x: %s\n", print->format);
	return (0);
}

int		format_x_upper(t_print_struct *print, va_list args)
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

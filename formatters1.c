/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatters1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 14:21:42 by Thunderpurt       #+#    #+#             */
/*   Updated: 2019/07/17 17:15:17 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		format_c(t_print_struct *print, va_list args)
{
	printf("format string c: %c\n", (char)print->flags[8]);
	return (0);
}

int		format_d(t_print_struct *print, va_list args);
{
	printf("format string d: %s\n", print->format);
	return (0);
}

int		format_f(t_print_struct *print, va_list args)
{
	printf("format string f: %s\n", print->format);
	return (0);
}

int		format_i(t_print_struct *print, va_list args)
{
	printf("format string i: %s\n", print->format);
	return (0);
}

int		format_o(t_print_struct *print, va_list args)
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

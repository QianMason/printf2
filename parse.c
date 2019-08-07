/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 16:49:47 by mqian             #+#    #+#             */
/*   Updated: 2019/08/06 16:11:50 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     parse_and_print(t_print_struct *print, va_list args)
{
	while (*(print->format) && print->format)
	{
		if (*(print->format) == '%')
		{
			(print->format)++;
			print->format = parse_params(print, print->format);
            if (print->flags[9] > 0 && print->flags[9] != 37)
			{
			    (print->count) += print_conversion(print, args); //function that will call mapping function to get specific function for proper specifier
				reset_flags(print);
			}
		}
		else
		{
			write(1, print->format, 1);
			(print->count)++;
			(print->format)++;
		}
	}
	return (print->count);
}

char *	parse_params(t_print_struct *print, char *format)
{
    char *ref;

    ref = format;
	while (*format)
	{
		parse_set_flags(print, format);
		//print_table(print);
        format++;
        if (print->flags[9] > 0 && print->flags[9] != 37)
            return (format);
		else if (print->flags[9] == 37)
		{
			write(1, "%", 1);
			(print->count)++;
			reset_flags(print);
			return (format);
		}
		else if (print->flags[9] == -1) //case where parse_set_flags found something that wasnt anything, so we write '%' since 
		{ //outer function moves format pointer over, and then start printing from there again
			write(1, "%", 1);
			(print->count)++;
			reset_flags(print);
			return (ref);
		}
    }
    return (ref); //reached end and didnt hit a % or a conversion specifier
}

void	parse_set_flags(t_print_struct *print, char *format)
{
	if (*format == '+')
		print->flags[0] = 1;
	else if (*format == '-')
		print->flags[1] = 1;
	else if (*format == '#')
		print->flags[2] = 1;
	else if (*format == '0' && print->flags[5] == 0 && print->flags[6] == 0)
		print->flags[3] = 1;
	else if (*format == ' ')
		print->flags[4] = 1;
    else if (atoi(format) > 0 && print->flags[6] == 0 && print->flags[5] == 0)
        print->flags[5] = atoi(format);
    else if (*format == '.')
        print->flags[6] = 1;
    else if (atoi(format) > 0 && print->flags[6] == 1 && print->flags[7] == 0)
        print->flags[7] = atoi(format);
    else if (*format == 'h' || *format == 'l' || *format == 'L')
        parse_set_len_mod(print, format);
    else if (is_conversion(format))
        print->flags[9] = (int)(*format);
	//else //within the format, the current char is none of the modifiers or params, so we simply stop considering and assign it a negative value
		//print->flags[9] = -1;
}

// char *	parse_params(t_print_struct *print, char *format)
// {
// 	while (*format)
// 	{
// 		parse_set_flags(print, format);
// 		if (atoi(*format) > 0) && print->flags[6] == 0)
// 		{
// 			print->flags[5] = atoi(*format);
// 			while (atoi(*format) != 0)
// 				format++;
// 		}
// 		if (*format == '.') //dot precision
// 		{
// 			format++; //move it over from the period
// 			if (atoi(*format) > 0)
// 			{
// 				print->flags[6] = atoi(*format);
// 				while (atoi(*format) != 0)
// 					format++;
// 			}
// 		}
// 		format = parse_set_len_mod(print, format);
// 		if (is_conversion(format))
// 		{
// 			print->flags[8] = (int)(*format); //ascii value
// 			return (format++);
// 		}
// 		if (*format == '%') // && print->flags[8] = 0; means we didnt encounter the other one so we break because this is wrong
// 		{
// 			print->flags[8] = 37;
// 			format++;
// 			return (format);
// 		}
// 		format++;
// 	}
// 	return (format);
// }

void    parse_set_len_mod(t_print_struct *print, char *format)
{
	if (*format == 'h' || *format == 'l')
	{
		if (*format == 'h')
		{
			if (print->flags[8] == 2) // then hh
				print->flags[8] = 1;
			else
				print->flags[8] = 2;
		}
		else // *format == 'l'
		{
			if (print->flags[8] == 3)
				print->flags[8] = 4;
			else
				print->flags[8] = 3;
		}
	}
	else if (*format == 'L')
		print->flags[8] = 5;
}

int		is_conversion(char *format)
{
	if (*format == 'c' || *format == 'd' || *format == 'f' || *format == 'i'
		|| *format == 's' || *format == 'o' || *format == 'p' || *format == 'u'
			|| *format == 'x' || *format == 'X' }} *format == '%')
			{
				return (1);
			}
	return (0);
}

int     print_conversion(t_print_struct *print, va_list args)
{
	int i;

	i = 0;
	i = print->formatters[letter_to_function((char)print->flags[9])](print->flags, args);
	return (i);
}


// int     print_conversion(t_print_struct *print, va_list args)
// {
//     int *i;

// 	*i = 0;
// 	if (print->flags[8] == 99)
// 		format_c(print, args. i);
// 	else if (print->flags[8] == 100)
// 		format_d(print, args, i);
// 	else if (print->flags[8] == 102)
// 		format_f(print, args, i);
// 	else if (print->flags[8] == 105)
// 		format_i(print, args, i);
// 	else if (print->flags[8] == 111)
// 		format_o(print, args, i);
// 	else if (print->flags[8] == 112)
// 		format_p(print, args, i);
// 	else if (print->flags[8] == 114)
// 		format_s(print, args, i);
// 	else if (print->flags[8] == 117)
// 		format_u(print, args, i);
// 	else if (print->flags[8] == 120)
// 		format_x(print, args, i);
// 	else if (print->flags[8] == 88)
// 		format_x_upper(print, args, i);
// }

/*
** THIS IS THE CURRENT MAPPING FOR THE FLAG CHECK FLAGS: (created per %)
**
**           +           0           0/1
**           -           1           0/1
**           #           2           0/1
**           0           3           0/1
**         ' '           4           0/1
**        minw           5           0/minw
**   precision           6           0/1
**	 precision           7           0/precision
** 	length mod           8           0 (no flags) or 1, 2, 3, 4 (hh, h, l, ll)
** conversions           9           letter to int, 37 (%) means we encountered another % before a conversion so get rid of everything and print the second %
*/

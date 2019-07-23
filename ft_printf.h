/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 16:43:01 by mqian             #+#    #+#             */
/*   Updated: 2019/07/23 16:18:59 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF
# define FT_PRINTF
# include <stdarg.h>
# include <stdio.h> //remove this later
# include "libft/includes/libft.h"
# include <unistd.h>

typedef int conversion(int flags[], va_list args);

typedef struct s_print_struct
{
	char *format; //holds the raw string itself
	conversion *formatters[10];
	int			count;
	// void (*format_c)(char, t_print_struct *);
	// void (*format_d)(signed int, t_print_struct *);
	// void (*format_f)(double, t_print_struct *);
	// void (*format_i)(signed int, t_print_struct *);
	// void (*format_o)(int, t_print_struct *);
	// void (*format_p)(void *, t_print_struct *);
	// void (*format_s)(char *, t_print_struct *);
	// void (*format_u)(unsigned int, t_print_struct *);
	// void (*format_x)(int, t_print_struct *)
	// void (*format_x_upper)(int, t_print_struct *);
	int			flags[10];
}				t_print_struct;

int		ft_printf(const char *format, ...);

t_print_struct *init_struct(t_print_struct *p, char *format, va_list args);
void	reset_flags(t_print_struct *p);
void	parse_set_flags(t_print_struct *print, char *format);

int		format_c(t_print_struct *print, va_list args); //format_c(char *format, int argnum);
int		format_d(t_print_struct *print, va_list args); //format_d(char *format, int argnum);
int		format_f(t_print_struct *print, va_list args); //format_f(char *format, int argnum);
int		format_i(t_print_struct *print, va_list args); //format_i(char *format, int argnum);
int		format_o(t_print_struct *print, va_list args); //format_o(char *format, int argnum);
int		format_p(t_print_struct *print, va_list args); //format_p(char *format, int argnum);
int		format_s(t_print_struct *print, va_list args); //format_s(char *format, int argnum);
int		format_u(t_print_struct *print, va_list args); //format_u(char *format, int argnum);
int		format_x(t_print_struct *print, va_list args); //format_x(char *format, int argnum);
int		format_x_upper(t_print_struct *print, va_list args); //format_x_upper(char *format, int argnum);
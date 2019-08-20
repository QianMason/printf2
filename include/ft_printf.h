/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 16:43:01 by mqian             #+#    #+#             */
/*   Updated: 2019/08/20 14:34:08 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdint.h>
# include <wchar.h>

typedef int		conversion(int flags[], va_list args);

typedef struct	s_print
{
	char		*format;
	conversion	*formatters[10];
	int			count;
	int			flags[10];
}				t_print;

/*
**				wrapper function
 */

int				ft_printf(const char *format, ...);

/*
**				struct init functions
 */

t_print			*init_struct(t_print *p, char *format);
void			reset_flags(t_print *p);

/*
**				parsing functions
 */

void			parse_set_flags(t_print *print, char *format);
int				parse_and_print(t_print *print, va_list args);
char			*parse_params(t_print *print, char *format);
void			parse_set_len_mod(t_print *print, char *format);
int				print_conversion(t_print *print, va_list args);
int				is_conversion(char *format);

/*
**				dispatch functions
 */

void			init_dispatch_table(conversion *f[]);
int				letter_to_function(char c);

/*
**				utility functions
 */
int				convert_to_hex(uintmax_t n, int flag);
int				convert_to_hex_upper(uintmax_t n, int flag);
int				convert_to_octal(uintmax_t n, int flag);
int				print_uint_max(uintmax_t n, int flag, int level);
int				print_float(intmax_t hold, int prec, int dot);
int				print_int_max(intmax_t n, int flag);
int				get_int_len(intmax_t n);
int				get_uint_len(uintmax_t n);
int				write_and_increment(wint_t c);
intmax_t		get_int_arg(int flags[], va_list args);
long double		get_float_arg(int flags[], va_list args);
uintmax_t		get_x_int_arg(int flags[], va_list args);

/*
**				formatters
 */

int				format_c(int flags[], va_list args);
int				format_d(int flags[], va_list args);
int				format_f(int flags[], va_list args);
int				format_i(int flags[], va_list args);
int				format_o(int flags[], va_list args);
int				format_p(int flags[], va_list args);
int				format_s(int flags[], va_list args);
int				format_u(int flags[], va_list args);
int				format_x(int flags[], va_list args);
int				format_x_upper(int flags[], va_list args);

int				format_c_left(int flags[], wint_t argument);
int				format_c_right(int flags[], wint_t argument);

int				format_d_left(int flags[], intmax_t argument, int len);
int				format_d_left_helper_1(int flags[], intmax_t argument, int len);
int				format_d_left_helper_2(int flags[], intmax_t argument);
int				format_d_left_helper_3(int flags[], intmax_t argument, int len);
int				format_d_sign(int flags[], intmax_t *arg);
int				format_d_right(int flags[], intmax_t argument, int len);
int				format_d_right_helper_1(int flags[], intmax_t arg, int len);
int				format_d_right_helper_2(int flags[], intmax_t arg, int len);
int				format_d_right_helper_3(int flags[], intmax_t arg, int len);

int				format_f_string(int flags[], long double arg, char **f_string);
char			*build_f_string(long double argument, int prec);
void			build_float(intmax_t hold, int prec, int len, char *f_string);
long			get_precision(long double f, int prec);
int				format_f_special(int flags[], long double argument, int count);
int				f_special_left(int flags[], intmax_t hold, int count);
int				f_special_right(int flags[], intmax_t hold, int count);
int				f_test_zero(int flags[], long double argument);
int				format_f_zero(int flags[], long double arg);
int				format_f_zero_left(int flags[], int count, long double arg);
int				format_f_zero_right(int flags[], int count, long double arg);
int				format_f_left(int flags[], char *f_string, long double arg);
int				format_f_right(int flags[], char *f, int len, long double arg);

int				format_o_left(int flags[], uintmax_t argument, int len);
int				format_o_left_helper_1(int flags[], uintmax_t arg, int len);
int				format_o_left_helper_2(int flags[], uintmax_t arg);
int				format_o_left_helper_3(int flags[], uintmax_t arg, int len);
int				format_o_right(int flags[], uintmax_t argument, int len);
int				format_o_right_helper_1(int flags[], uintmax_t arg, int len);
int				format_o_right_helper_2(int flags[], uintmax_t arg, int len);
int				format_o_right_helper_3(int flags[], uintmax_t arg, int len);

int				format_p_left(int flags[], uintmax_t dec, int len);
int				format_p_left_helper_1(int flags[], uintmax_t dec, int len);
int				format_p_left_helper_2(int flags[], uintmax_t dec);
int				format_p_left_helper_3(int flags[], uintmax_t dec, int len);
int				format_p_right(int flags[], uintmax_t dec, int len);
int				format_p_right_helper_1(int flags[], uintmax_t dec, int len);
int				format_p_right_helper_2(int flags[], uintmax_t dec, int len);
int				format_p_right_helper_3(int flags[], uintmax_t dec, int len);
int				format_p_zero(int flags[]);
int				format_p_zero_left(int flags[], int count);
int				format_p_zero_right(int flags[], int count);

int				format_s_left(int flags[], char *temp, int len);
int				format_s_left_helper_1(int flags[], char *temp, int len);
int				format_s_left_helper_2(int flags[], char *temp);
int				format_s_left_helper_3(int flags[], char *temp, int len);
int				format_s_right(int flags[], char *temp, int len);
int				format_s_right_helper_1(int flags[], char *temp, int len);
int				format_s_right_helper_2(int flags[], char *temp);
int				format_s_right_helper_3(int flags[], char *temp, int len);

int				format_u_left(int flags[], uintmax_t argument, int len);
int				format_u_left_helper_1(int flags[], uintmax_t arg, int len);
int				format_u_left_helper_2(int flags[], uintmax_t arg);
int				format_u_left_helper_3(int flags[], uintmax_t arg, int len);
int				format_u_right(int flags[], uintmax_t argument, int len);
int				format_u_right_helper_1(int flags[], uintmax_t arg, int len);
int				format_u_right_helper_2(int flags[], uintmax_t arg, int len);
int				format_u_right_helper_3(int flags[], uintmax_t arg, int len);

int				format_x_left(int flags[], uintmax_t argument, int len);
int				format_x_left_helper_1(int flags[], uintmax_t arg, int len);
int				format_x_left_helper_2(int flags[], uintmax_t arg);
int				format_x_left_helper_3(int flags[], uintmax_t arg, int len);
int				format_x_right(int flags[], uintmax_t argument, int len);
int				format_x_right_helper_1(int flags[], uintmax_t arg, int len);
int				format_x_right_helper_2(int flags[], uintmax_t arg, int len);
int				format_x_right_helper_3(int flags[], uintmax_t arg, int len);

int				format_x_upper_left(int flags[], uintmax_t argument, int len);
int				format_x_upper_lh1(int flags[], uintmax_t argument, int len);
int				format_x_upper_lh2(int flags[], uintmax_t argument);
int				format_x_upper_lh3(int flags[], uintmax_t argument, int len);
int				format_x_upper_right(int flags[], uintmax_t argument, int len);
int				format_x_upper_rh1(int flags[], uintmax_t argument, int len);
int				format_x_upper_rh2(int flags[], uintmax_t argument, int len);
int				format_x_upper_rh3(int flags[], uintmax_t argument, int len);

#endif

# include <stdarg.h>
# include <stdio.h> //remove this later
# include <unistd.h>
# include <stdlib.h>

typedef int conversion(int flags[], va_list args);

typedef struct s_print_struct
{
	char *format; //holds the raw string itself
	int			flags[9];
	conversion *formatters[10];
}				t_print_struct;

int		format_c(int flags[], va_list args)
{
	printf("format string c: %c\n", (char)flags[8]);
	return (0);
}

int		format_d(int flags[], va_list args)
{
	printf("format string d");
	return (0);
}

int		format_f(int flags[], va_list args)
{
	printf("format string f");
	return (0);
}

int		format_i(int flags[], va_list args)
{
	printf("format string i");
	return (0);
}

int		format_o(int flags[], va_list args)
{
	printf("format string o");
	return (0);
}

int		format_p(int flags[], va_list args)
{
	printf("format string p");
	return (0);
}

int		format_s(int flags[], va_list args) //first one you are working on 
{
	int count;
	int precision;
	int minw;
	char *temp;
	
	count = 0;
	precision = flags[6];
	temp = va_arg(args, char *);
	while (precision-- > 0 && *temp)
	{
		//ft_putchar(*temp);
		write(1, temp, 1);
		count++;
		temp++;
	}
	while (count < flags[5])
	{
		//ft_putchar(' ');
		write(1, " ", 1);
		count++;
	}
	printf("value of count being returned: %d\n", count);
	return (count);
}

int		format_u(int flags[], va_list args)
{
	printf("format string u");
	return (0);
}

int		format_x(int flags[], va_list args)
{
	printf("format string x");
	return (0);
}

int		format_x_upper(int flags[], va_list args)
{
	printf("format string X(upper)");
	return (0);
}

void init_dispatch_table(conversion *f[])
{
	f[0] = format_c;
    f[1] = format_d;
    f[2] = format_f;
    f[3] = format_i;
	f[4] = format_o;
	f[5] = format_p;
	f[6] = format_s;
	f[7] = format_u;
	f[8] = format_x;
	f[9] = format_x_upper;
}

int     letter_to_function(char c)
{
    if (c == 'c')
        return ((int)(c - 99));
    else if (c == 'd')
        return ((int)(c - 99));
    else if (c == 'f')
        return ((int)(c - 100));
    else if (c == 'i')
        return ((int)(c - 102));
    else if (c == 'o')
        return ((int)(c - 107));
    else if (c == 'p')
        return ((int)(c - 107));
    else if (c == 's')
        return ((int)(c - 109));
    else if (c == 'u')
        return ((int)(c - 110));
    else if (c == 'x')
        return ((int)(c - 112));
    else if (c == 'X')
        return ((int)(c - 79));
    else
        return (0);
}

int     print_conversion(t_print_struct *print, va_list args)
{
	int i;

	i = 0;
	printf("in print conversion func\n");
	i = print->formatters[letter_to_function((char)print->flags[8])](print->flags, args);
}

void    print_table(t_print_struct *print)
{
    for (int i = 0; i < 9; i++)
    {
        printf("value of table index[%d]: %d\n", i, print->flags[i]);
    }
}

int		is_conversion(char *format)
{
	if (*format == 'c' || *format == 'd' || *format == 'f' || *format == 'i'
		|| *format == 's' || *format == 'o' || *format == 'p' || *format == 'u'
			|| *format == 'x' || *format == 'X')
			{
				return (1);
			}
	return (0);
}

char *	parse_set_len_mod(t_print_struct *print, char *format)
{
	if (*format == 'h' || *format == 'l')
	{
		if (*format == 'h')
		{
			if ((*(format + 1)) == 'h') // then hh
			{
				print->flags[7] = 1;
				format++;
			}
			else
				print->flags[7] = 2;
		}
		else
		{
			if ((*(format + 1)) == 'l')
			{
				print->flags[7] = 4;
				format++;
			}
			else
				print->flags[7] = 3;
		}
	}
	return (format);
}

void	reset_flags(t_print_struct *p)
{
	int i;

	i = 0;
	while (i < 9)
	{
		p->flags[i] = 0;
		i++;
	}
}

t_print_struct *init_struct(t_print_struct *p, char *format, va_list args)
{
	int i;

	i = 0;
	if (!(p = (t_print_struct *)malloc(sizeof(t_print_struct))))
		return (NULL);
	p->format = format;
	init_dispatch_table(p->formatters);
	reset_flags(p);
	return (p);
}

void	parse_set_flags(t_print_struct *print, char *format)
{
	if (*format == '+')
		print->flags[0] = 1;
	else if (*format == '-')
		print->flags[1] = 1;
	else if (*format == '#')
		print->flags[2] = 1;
	else if (*format == '0')
		print->flags[3] = 1;
	else if (*format == ' ')
		print->flags[4] = 1;
    else if (atoi(format) > 0 && print->flags[6] == 0)
        print->flags[5] = atoi(format);
    else if (*format == '.')
        print->flags[6] = 1;
    else if (atoi(format) > 0)
        print->flags[6] = atoi(format);
    else if (*format == 'h' || *format == 'l')
        format = parse_set_len_mod(print, format);
    else if (is_conversion(format))
        print->flags[8] = (int)(*format);
}

char *	parse_params(t_print_struct *print, char *format)
{
    char *ref;

    ref = format;
	while (*format)
	{
		parse_set_flags(print, format);
        format++;
        if (print->flags[8] > 0 && print->flags[8] != 37)
            return (format);
		else if (print->flags[8] == 37)
			return (ref);
    }
    return (ref); //reached end and didnt hit a % or a conversion specifier
}


int     parse_and_print(t_print_struct *print, va_list args, int count)
{
	while (*(print->format))
	{
		if (*(print->format) == '%')
		{
			(print->format)++;
			if (print->flags[8] == 37)
			{
				write(1, print->format, 1);
				reset_flags(print);
				continue;
			}
			print->format = parse_params(print, print->format);
            if (print->flags[8] > 0 && print->flags[8] != 37)
			{
			    count += print_conversion(print, args); //function that will call mapping function to get specific function for proper specifier
				reset_flags(print);
			}
		}
		else
		{
			write(1, print->format, 1);
			(print->format)++;
		}
	}
	return (count);
}


int		ft_printf(const char *format, ...)
{
	int				*count;
	t_print_struct	*print;
	va_list			args;

	count = 0;
	va_start(args, format);
	print = init_struct(print, (char*)format, args);
	count = parse_and_print(print, args, count);
	return (count);
}

int     main(void)
{
    int j = ft_printf("%-+5.6s", "this is a string");
    printf("length of print: %d\n", j);
    return (0);
}

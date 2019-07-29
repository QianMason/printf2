# include <stdarg.h>
# include <stdio.h> //remove this later
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

typedef int conversion(int flags[], va_list args);

typedef struct s_print_struct
{
	char *format; //holds the raw string itself
	int			flags[10];
	int count;
	conversion *formatters[10];
}				t_print_struct;

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

intmax_t    get_int_arg(int flags[], va_list args)
{
    intmax_t argument;

    if (flags[8] == 1)
        argument = va_arg(args, signed char);
    else if (flags[8] == 2)
        argument = va_arg(args, short);
    else if (flags[8] == 3)
        argument = va_arg(args, long);
    else if (flags[8] == 4)
        argument = va_arg(args, long long);
    else
        argument = va_arg(args, int);
    return (argument);
}

int     get_int_len(intmax_t n)
{
    int count;

    count = 0;
    while (n)
    {
        n /= 10;
        count++;
    }
    return (count);
}

int    write_and_increment(char c)
{
    write(1, &c, 1);
    return (1);
}

void	ft_putnbr(int n)
{
	unsigned int num;

	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	num = n;
	if (num > 9)
	{
		ft_putnbr(num / 10);
		ft_putnbr(num % 10);
	}
	if (num <= 9)
		ft_putchar((num % 10) + 48);
}


int    convert_to_hex(uintmax_t n, int flag)
{
    uintmax_t temp;
    char c;
    int count;

    if (!n)
        return (0);
    temp = n % 16;
    if (temp < 10)
        c = temp + 48;
    else
        c = temp + 87;
    count = convert_to_hex(n/16, flag);
    if (flag == 1)
        write(1, &c, 1);
    count++;
    return (count);
}
int		d_right_helper_3(int flags[], int arg_len, intmax_t argument, int count)
{
    printf("drh3\n");
	while (count < flags[5] - flags[7] - 1)
		count += write_and_increment(' ');
	if (argument == 0)
		count += write_and_increment(' ');
	else if (argument < 0)
	{
		count += write_and_increment('-');
		argument *= -1;
	}
	else
		count += write_and_increment('+');
	while (count < flags[5] - arg_len)
		count += write_and_increment('0');
	ft_putnbr(argument);
	count += arg_len;
	return (count);
}

int		d_right_helper_4(int flags[], int arg_len, intmax_t argument, int count)
{
    printf("drh4\n");
	if (argument == 0)
	{
		ft_putnbr(argument);
		count++;
	}
	else if (argument < 0)
	{
		count += write_and_increment('-');
		argument *= -1;
	}
	else
		count += write_and_increment('+');
	ft_putnbr(argument);
	count += arg_len;
	return (count);
}

int		d_right_helper_5(int flags[], int arg_len, intmax_t argument, int count)
{
    printf("drh5\n");
    if (flags[6] == 0 && flags[3] == 1) //minw > arg_len > precision
    {
        if (argument < 0)
        {
            count += write_and_increment('-');
            argument *= -1;
        }
        while (count < flags[5] - arg_len)
            count += write_and_increment('0');
    }
    else if (flags[6] == 1 || flags[3] == 0)
    {
        while (count < flags[5] - arg_len - 1)
            count += write_and_increment(' ');
        if (argument < 0)
        {
            count += write_and_increment('-');
            argument *= -1;
        }
        else
            count += write_and_increment(' ');
    }
    ft_putnbr(argument);
    count += arg_len;
	return (count);
}

int     d_right_helper_6(int flags[], int arg_len, intmax_t argument, int count)
{
    printf("drh6\n");
    if (argument > 0)
        write(1, "+", 1);
    else if (argument < 0)
    {
        write(1, "-", 1);
        argument *= -1;
    }
    if (flags[7] > arg_len)
    {
        while (count < flags[7] - arg_len)
            count += write_and_increment('0');
    }
    ft_putnbr(argument);
    count += arg_len;
    if (argument != 0)
        count++;
    return (count);
}

int     d_right_helper_7(int flags[], int arg_len, intmax_t argument, int count)
{
    printf("in d_right_helper_7\n");
    while (count < flags[5] - flags[7] - 1)
        count += write_and_increment(' ');
    if (argument < 0)
    {
        count += write_and_increment('-');
        argument *= -1;
    }
    while (count < flags[5] - arg_len)
        count += write_and_increment('0');
    ft_putnbr(argument);
    count += arg_len;
    return (count);
}

int     d_right_helper_8(int flags[], int arg_len, intmax_t argument, int count)
{
    printf("in d_right_helper_8\n");
    if (arg_len > flags[5])
    {
        ft_putnbr(argument);
        count += arg_len;
        if (argument < 0)
            count++;
    }
    else
    {
        printf("went here instead\n");
        //printf("value of flags[3] == %d\n", flags[3]);
        // this portion of code below is identical to d_right_helper_5, so maybe just use that?
        if (flags[6] == 0 && flags[3] == 1) //minw > arg_len > precision
        {
            if (argument < 0)
            {
                count += write_and_increment('-');
                argument *= -1;
            }
            while (count < flags[5] - arg_len)
                count += write_and_increment('0');
        }
        else if (flags[6] == 1 || flags[3] == 0)
        {
            while (count < flags[5] - arg_len - 1)
                count += write_and_increment(' ');
            if (argument < 0)
            {
                count += write_and_increment('-');
                argument *= -1;
            }
            else
                count += write_and_increment(' ');
        }
        ft_putnbr(argument);
        count += arg_len;
    }
    return (count);
}

int     d_right_helper_9(int flags[], int arg_len, intmax_t argument, int count)
{
    //printf("in d_right_helper_9\n");
    if (argument < 0)
        write(1, "-", 1);
    if (flags[7] > arg_len) //precision greater than arg_len, need to pad with 0s
    {
        while (count < flags[7] - arg_len)
            count += write_and_increment('0');
        if (argument < 0)
        {
            count++;
            argument *= -1;
        }
        ft_putnbr(argument);
        count += arg_len;
    }
    else //arg_len >= flags[7], arg_len >precision >= flags[5], so print prepension and then just print the number since its right justified.
    {
        if (argument < 0)
        {
            count++;
            argument *= -1;
        }
        ft_putnbr(argument);
        count += arg_len;
    }
    return (count);
}


int     d_right_helper_1(int flags[], int arg_len, intmax_t argument, int count)
{
    printf("in d_right_helper_1\n");
    if (flags[5] > flags[7]) //minw greater than precision
    {
        if (flags[7] > arg_len) //precision is greater than arg_len
            count += d_right_helper_3(flags, arg_len, argument, count);
        else //flags[7] <= arg_len, precision is less than or equal to arg_len so ignore
        {
            if (arg_len > flags[5])
                count += d_right_helper_4(flags, arg_len, argument, count);
            else //arg_len <= minw (flags[5]) precision ignored
                count += d_right_helper_5(flags, arg_len, argument, count);
        }
    }
    else //minw flags[5] <= precision flags[7]
        count += d_right_helper_6(flags, arg_len, argument, count);
    return (count);
}

int     d_right_helper_2(int flags[], int arg_len, intmax_t argument, int count)
{
    printf("in d_right_helper_2 no prepended +/-\n");
    if (flags[5] > flags[7]) //minw greater than precision
    {
        if (flags[7] > arg_len)
            count += d_right_helper_7(flags, arg_len, argument, count);
        else // arg_len >= precision (flags[7])
            count += d_right_helper_8(flags, arg_len, argument, count);
    }
    else // minw <= than precision (flags[5] <= flags[7]) essentially left justified
        count += d_right_helper_9(flags, arg_len, argument, count);
    return (count);
}

int		format_d_right(int flags[], intmax_t argument)
{
    printf("in format_d_right\n");
	int count;
	int arg_len;

	count = 0;
	arg_len = get_int_len(argument);
	//printf("argument: %d, argument length: %d\n", argument, arg_len);
	if (flags[0] == 1) // prepend a + or - based on argument sign
		count += d_right_helper_1(flags, arg_len, argument, count);
	else //no +/- prepensions
		count += d_right_helper_2(flags, arg_len, argument, count);
	return (count);
}

int		format_d_left_helper_4(int flags[], int arg_len, intmax_t argument, intmax_t orig)
{
	int count;

	count = 0;
	if (flags[7] > arg_len)
	{
		while (count < flags[7] - arg_len)
			count += write_and_increment('0');
		ft_putnbr(argument);
		count += (orig != 0) ? arg_len + 1: arg_len;
		while (count < flags[5])
			count += write_and_increment(' ');
	}
	else //precision is less than argument length or is zero
	{
		ft_putnbr(argument);
		count += (orig != 0) ? arg_len + 1: arg_len;
		while (count < flags[5])
			count += write_and_increment(' ');
	}
	return (count);
}

int		format_d_left_helper_1(int flags[], int arg_len, intmax_t argument, int count)
{
    printf("in format_d_left_helper_1\n");
    intmax_t orig;

    orig = argument;
	if (argument < 0)
	{
		write(1, "-", 1);
		argument *= -1; //convert to positive
	}
	else if (argument > 0)
		write(1, "+", 1);
	count += format_d_left_helper_4(flags, arg_len, argument, orig);
	return (count);
}

int		format_d_left_helper_3(int flags[], int arg_len, intmax_t argument, intmax_t orig)
{
    //printf("int format_d_left_helper_3\n");
	int count;

	count = 0;
	if (flags[7] > arg_len)
	{
	    //printf("in first part\n");
		while (count < flags[7] - arg_len)
			count += write_and_increment('0');
		ft_putnbr(argument);
		count += (orig < 0) ? arg_len + 1: arg_len; //need to update count here to handle tis condition
		while (count < flags[5])
			count += write_and_increment(' ');
	}
	else //precision is less than argument length or is zero/not present
	{
	    //printf("in second part\n");
		ft_putnbr(argument);
		count += (orig < 0) ? arg_len + 1: arg_len;
		while (count < flags[5] && (flags[3] == 0 || flags[6] == 1)) //precision is ignored so print ' 's if the 0 flag is not present
			count += write_and_increment(' ');
		while (count < flags[5] && flags[3] == 1 && flags[6] == 0) //precision is ignored so print '0's if the 0 flag is present
			count += write_and_increment('0');
	}
	return (count);
}

int		format_d_left_helper_2(int flags[], int arg_len, intmax_t argument, int count)
{
    printf("in format_d_left_helper_2\n");
	intmax_t orig;

	orig = argument;
	if (argument < 0)
	{
		write(1, "-", 1);
		argument *= -1; //convert to positive
	}
	count += format_d_left_helper_3(flags, arg_len, argument, orig);
	return (count);
}

int		format_d_left(int flags[], intmax_t argument) //left align
{
    //printf("in format_d_left\n");
	int count;
	int arg_len;

	count = 0;
	arg_len = get_int_len(argument);
	if (flags[0] == 1) // '+' seen which means prepend a + or - based on if the number is positive or negative
		count += format_d_left_helper_1(flags, arg_len, argument, count);
	else //flags[0] == 0 so no prepended + or - so 0 flag is not overrided
		count += format_d_left_helper_2(flags, arg_len, argument, count);
	return (count);
}

int     format_p_left_helper_1(int flags[], uintmax_t dec, int len)
{
    // if precision is >= minw && >= arg_len
    // left aligned so no 0 consideration
    // but since precision might be greater, we print 0 until precision
    int count;

    count = 0;
    while (count < flags[7] - len)
        count += write_and_increment('0');
    count += convert_to_hex(dec, 1);
    return (count);
}

int format_p_left_helper_2(int flags[], uintmax_t dec, int len)
{
    //if minw >= len && minw >= precision
    //if len >= precision
    //left aligned
    int count;

    count = 0;
    count += convert_to_hex(dec, 1);
    while (count + 2 < flags[5])
        count += write_and_increment(' ');
    return (count);
}

int format_p_left_helper_3(int flags[], uintmax_t dec, int len)
{
    // minw >= precision && minw >= arg_len
    // precision > arg_len
    int count;

    count = 0;
    while (count < flags[7] - len)
        count += write_and_increment('0');
    count += convert_to_hex(dec, 1);
    while (count + 2 < flags[5]) //because now we have to make sure, that the 0x is included in minw count
        count += write_and_increment(' ');
    return (count);
}

int     format_p_left_helper(int flags[], uintmax_t dec, int len)
{
    int count;

    write(1, "0x", 2);
    count += 2;
    if (len >= flags[5] && len >= flags[7])
    {
        count += convert_to_hex(dec, 1);
        printf("above = len greatest\n");
    }
    else if (flags[7] >= flags[5] && flags[7] >= len)
    {
        count += format_p_left_helper_1(flags, dec, len);
        printf("above format_p_left_helper_1\n");
    }
    else if (flags[5] >= len && flags[5] >= flags[7])
    {
        if (len >= flags[7])
        {
            count += format_p_left_helper_2(flags, dec, len);
            printf("above was format_p_left_helper_2\n");
        }
        else // minw >= precision > len
        {
            count += format_p_left_helper_3(flags, dec, len);
            printf("left format_p_left_helper_3\n");
        }
    }
    return (count);
}

int		format_p_right_helper_1(int flags[], uintmax_t dec, int len)
{
	// precision greatest, essentially left justified even though its right justified
	//already wrote the "0x", just write the rest of the zeros up to precision - length of the argument, then fill the rest with the converetd hex
	int count;

	count = 0;
	while (count < flags[7] - len)
		count += write_and_increment('0');
	count += convert_to_hex(dec, 1);
	return (count);
}

int		format_p_right_helper_2(int flags[], uintmax_t dec, int len)
{
	// minw is greatest
	// arg_len >= precision
	int count;

	count = 0;
	while (count < flags[5] - len - 2)
		count += write_and_increment(' ');
	write(1, "0x", 2);
	count += 2;
	count += convert_to_hex(dec, 1);
	return (count);
}

int		format_p_right_helper_3(int flags[], uintmax_t dec, int len)
{
	//minw >= precision && minw >= arg_len
	// min precision > arg_len
	int count;

	count = 0;
	if (flags[5] - flags[7] > 2)
	{
		while (count < flags[5] - flags[7] - 2)
			count += write_and_increment(' ');
		write(1, "0x", 2);
		count += 2;
		while (count < flags[5] - len)
			count += write_and_increment('0');
		count += convert_to_hex(dec, 1);
	}
	else // if (flags[5] - flags[7] <= 2)
	{
		write(1, "0x", 2);
		count += 2;
		count += format_p_left_helper_1(flags, dec, len);
	}
	return (count);
}

int     format_p_right_helper(int flags[], uintmax_t dec, int len)
{
    int count;

    count = 0;
    if (len >= flags[5] && len >= flags[7])
	{
	    printf("regular call\n");
		write(1, "0x", 2);
		count += 2;
        count += convert_to_hex(dec, 1);
	}
    else if (flags[7] >= flags[5] && flags[7] >= len)
	{
	    printf("in format_p_right_helper_1\n");
		write(1, "0x", 2);
		count += 2;
        count += format_p_right_helper_1(flags, dec, len);
	}
    else if (flags[5] >= len && flags[5] >= flags[7])
    {
        if (len >= flags[7])
        {
            printf("in format_p_right_helper_2\n");
            count += format_p_right_helper_2(flags, dec, len);
        }
        else // minw >= precision > len
        {
            printf("in format_p_right_helper_3\n");
            count += format_p_right_helper_3(flags, dec, len);
        }
    }
    return (count);
}

int		format_s_left_helper(int flags[], char *temp, int len)
{
	int		count;

	count = 0;
	while (count < len) //putchar til end of string
	{
		count++;
		write(1, temp, 1);
		temp++;
	}
	while (count < flags[5]) //pad down spaces until end of minw
	{
		write(1, " ", 1);
		count++;
	}
	return (count);
}

int		format_s_left(int flags[], char *temp, int len)
{
	int 	count;

	count = 0;
	if (flags[6] > 0 && flags[6] < len)
	{
		while (flags[6]-- > 0)
		{
			write(1, temp, 1);
			count++;
			temp++;
		}
		while (count < flags[5])
		{
		    count++;
			write(1, " ", 1);
		}
	}
	else //no consideration for precision, as long as minw is greater than len, pad til minw, else, just write out the string
		count = format_s_left_helper(flags, temp, len);
	return (count);
}

int		format_s_right_helper(int flags[], char *temp, int len)
{
	int count;

	count = 0;
	if (flags[6] > flags[5]) //precision greater than minw, no need to justify
	{
	    printf("precision %d, minw %d\n", flags[6], flags[5]);
		while (flags[6]-- > 0)
		{
			count++;
			write(1, temp++, 1);
			//temp++;
		}
	}
	else //precision not as great as minw, need to pad the left side with stuff
	{
		while (count < flags[5] - flags[6])
		{
			count++;
			write(1, " ", 1);
		}
		while (flags[6]-- > 0)
		{
			count++;
			write(1, temp++, 1);
			//temp++;
		}
	}
	return (count);
}

int		format_s_right(int flags[], char *temp, int len)
{
	int pad;
	int	count;

	pad = 0;
	count = 0;
	if (flags[6] > 0 && flags[6] <= len)
	{
	    //printf("format_s_right_helper call\n");
		count = format_s_right_helper(flags, temp, len);
	}
	else //no considerations for precision again since its greater than strlen or 0 so all we do is print normally
	{
		if (len >= flags[5])
			count = format_s_left(flags, temp, len); //then it just becomes the left justify case
		else //len < minw, so we need padding
		{
			while (pad++ < flags[5] - len)
			{
				count++;
				write(1, " ", 1);
				temp++;
			}
			while (count++ < len)
				write(1, temp++, 1);
				//temp++
		}
	}
	return (count);
}

int		format_c(int flags[], va_list args)
{
	int count;
	char c;

    count = 0;
	c = va_arg(args, int);
	if (flags[1] == 1) //left justify
	{
	    //printf("left justify call\n");
		count++;
		write(1, &c, 1);
		//printf("value of count before while loop: %d\n", count);
		while (count < flags[5])
		{
			write(1, " ", 1);
			count++;
		}
	}
	else
	{
	    //printf("right justify call\n");
		while (count < flags[5] - 1)
		{
			write(1, " ", 1);
			count++;
		}
		write(1, &c, 1);
		count++;
	}
	return (count);
}

int		format_d(int flags[], va_list args)
{
    //printf("in format_d\n");
	int count;
	intmax_t argument;

	count = 0;
	argument = get_int_arg(flags, args);
	if (flags[1] == 1) //left align
		count = format_d_left(flags, argument);
	else
		count = format_d_right(flags, argument);
	return (count);
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
	int count;
	void *temp;
	uintmax_t dec;
	int len;

	count = 0;
	temp = va_arg(args, void*);
	dec = (uintmax_t)temp;
	len = convert_to_hex(dec, 0);
	if (!temp)
	{
		write(1, "0x0", 3);
		count += 3;
	}
	else if (flags[1] == 1) //left justify
		count += format_p_left_helper(flags, dec, len);
	else //right justify
		count += format_p_right_helper(flags, dec, len);
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
		    //printf("format s left call\n");
		    count = format_s_left(flags, temp, len); //non default behavior
		}
		else
		{
		    //printf("format s right call\n");
			count = format_s_right(flags, temp, len); //default behavior
		}
	}
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
	i = print->formatters[letter_to_function((char)print->flags[9])](print->flags, args);
	return (i);
}

void    print_table(t_print_struct *print)
{
    for (int i = 0; i < 10; i++)
    {
        printf("value of table index[%d]: %d\n", i, print->flags[i]);
    }
}

int		is_conversion(char *format)
{
	if (*format == 'c' || *format == 'd' || *format == 'f' || *format == 'i'
		|| *format == 's' || *format == 'o' || *format == 'p' || *format == 'u'
			|| *format == 'x' || *format == 'X' || *format == '%')
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
	while (i < 10)
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
	p->count = 0;
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
    else if (*format == 'h' || *format == 'l')
        parse_set_len_mod(print, format);
    else if (is_conversion(format))
        print->flags[9] = (int)(*format);
	//else //within the format, the current char is none of the modifiers or params, so we simply stop considering and assign it a negative value
		//print->flags[9] = -1;
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


int     parse_and_print(t_print_struct *print, va_list args)
{
	while (*(print->format) && print->format)
	{
		if (*(print->format) == '%')
		{
			(print->format)++;
			print->format = parse_params(print, print->format);
			//print_table(print);
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

int		ft_printf(const char *format, ...)
{
	t_print_struct	*print;
	va_list			args;

	va_start(args, format);
	print = init_struct(print, (char*)format, args);
	print->count = parse_and_print(print, args);
	return (print->count);
}


int     main(void)
{
    printf("format string: %%-20.19p\n");
    int i = 23002342;
    int *j = &i;
    int k = printf("%-.19p", j);
    printf("to the left is printf call\n");
    int l = ft_printf("%-.19p", j);
    printf("\nValue of printf call: %d\n", k);
    printf("Value of ft_printf call: %d\n", l);
    return (0);
}



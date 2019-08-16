# include <stdarg.h>
# include <stdio.h> //remove this later
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <float.h>

typedef int conversion(int flags[], va_list args);

typedef struct s_print_struct
{
	char *format; //holds the raw string itself
	int			flags[10];
	int count;
	conversion *formatters[10];
}				t_print_struct;

int    write_and_increment(char c)
{
    write(1, &c, 1);
    return (1);
}

size_t		ft_strlen(const char *s)
{
	int		count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

void	ft_putstr(const char *s)
{
	write(1, s, ft_strlen(s));
}

long	get_prec_num_f(long double d, int prec)
{
	int		neg;
	int		i;

	i = -1;
	neg = (d < 0 ? -1 : 1);
	d *= neg;
	while (++i < prec)
		d *= 10;
	d += 0.5;
	d *= neg;
	return ((long)d);
}

void    build_float(intmax_t hold, int prec, int len, char *f_string)
{
    char c;
    intmax_t temp;
    int index;

    index = len;
    if (hold < 0)
        hold *= -1;
    while (--index >= 0)
    {
        if (index == len - prec - 1 && prec > 0)
        {
            f_string[index] = '.';
            continue;
        }
        temp = hold % 10;
        c = temp + 48;
        f_string[index] = c;
        hold /= 10;
    }
}

int     f_prec_default(int flags[])
{
    if (flags[6] == 0 || (flags[6] == 1 && flags[7] == 0))
        return (1);
    return (0);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*c;

	i = 0;
	c = s;
	if (n == 0)
	{
		return ;
	}
	while (i < n)
	{
		*c = '\0';
		i++;
		c++;
	}
}

void	*ft_memalloc(size_t size)
{
	void	*alloc;
	int		i;

	i = 0;
	alloc = (void *)malloc(sizeof(char) * size);
	if (!alloc)
	{
		return (NULL);
	}
	ft_bzero(alloc, size);
	return (alloc);
}

char	*ft_strnew(size_t size)
{
	char *temp;

	temp = (char *)ft_memalloc(size + 1);
	return (temp);
}

long double     get_float_arg(int flags[], va_list args)
{
    if (flags[8] == 5) //'L' flag shown
        return (va_arg(args, long double));
    return (va_arg(args, double));
}


int     print_float(intmax_t hold, int prec, int dot)
{
    int count;
    intmax_t temp;
    char c;

    count = 0;
    if (!hold)
        return (0);
    temp = hold % 10;
    c = temp + 48;
    count = print_float(hold / 10, prec, dot + 1);
    write(1, &c, 1);
    count++;
    if (dot == prec)
    {
        write(1, ".", 1);
        count++;
    }
    return (count);
}

int    format_d_sign(int flags[], intmax_t *arg)
{
    int count;

    count = 0;

    if (*arg < 0) //negative the value is always written
    {
        count += write_and_increment('-');
        *arg *= -1;
    }
    else if (flags[0] == 1 && *arg >= 0) //next in line is if there is a + flag, which means show the '+' if positive
        count += write_and_increment('+');
    else if (flags[4] == 1) //final check is if ' ' flag is present, then write in a space initially
        count += write_and_increment(' ');
    return (count);
}

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

char	*ft_ftoa(long double d)
{
	char	*s;
	long	tmp;
	int		len;
	int		neg;

	neg = (d < 0 ? -1 : 1);
	len = (d < 0 ? 1 : 0);
	d *= neg;
	tmp = (long)d;
	while (tmp > 0 && len++ >= 0)
		tmp /= 10;
	while (d - (long)d != 0 && len++ >= 0)
		d *= 10;
	s = ft_strnew(len);
	while (--len >= 0)
	{
		s[len] = (long)d % 10 + '0';
		d /= 10;
		if (neg == -1 && len == 1)
		{
			s[0] = '-';
			break ;
		}
	}
	return (s);
}

int     get_float_len(long double f)
{
    int len;
    intmax_t hold;
    printf("f in func: %Lf\n", f);
    hold = (intmax_t)f; //cast to int to get that portion of the number;

    printf("hold: %lld\n", hold);
    len = 0;
    if (f < 0) //for negative value
        len += 1;
    f = (f < 0) ? -f : f;
    printf("f: %Lf\n", f);
	while (hold > 0 && len++ >= 0)
		hold /= 10;
	while (f - (long)f != 0 && len++ >= 0)
	{
		f *= 10;
		//printf("len now: %d, f now: %Lf\n", len, f);
	}
	//printf("len + 1: %d\n", len + 1);
    return (len + 1); //for decimal
}

int    convert_to_hex_upper(uintmax_t n, int flag)
{
    uintmax_t temp;
    char c;
    int count;
    if (!n)
        return (0);
    temp = n % 16;
    if (temp > 10)
        c = temp + 55;
    else
        c = temp + 48;
    count = convert_to_hex_upper(n/16, flag);
    if (flag == 1)
        write(1, &c, 1);
    count++;
    return (count);
}

int     get_uint_len(uintmax_t n)
{
    int count;

    count = 0;
    if (n == 0)
        return (1);
    while (n)
    {
        n /= 10;
        count++;
    }
    return (count);
}

int     convert_to_octal(uintmax_t n, int flag)
{
    uintmax_t temp;
    char c;
    int count;
    if (!n)
        return (0);
    temp = n % 8;
    c = temp + 48;
    count = convert_to_octal(n / 8, flag);
    if (flag == 1)
        write(1, &c, 1);
    count++;
    return (count);
}


intmax_t    get_int_arg(int flags[], va_list args)
{
    intmax_t argument;
    if (flags[8] == 1)
        argument = va_arg(args, int);
    else if (flags[8] == 2)
        argument = va_arg(args, int);
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

char    *build_f_string(long double argument, int prec)
{
    char *f_string;
    intmax_t hold;
    int len;

    hold = (intmax_t)argument;
    len = (prec > 0) ? get_int_len(hold) + prec + 1 : get_int_len(hold);
    f_string = ft_strnew(len); //len of front part, prec, .
    ft_bzero((void *)f_string, len + 1);
    hold = get_prec_num_f(argument, prec);
    build_float(hold, prec, len, f_string);
    return (f_string);
}

int     print_uint_max(uintmax_t n, int flag, int level)
{
    uintmax_t temp;
    char c;
    int count;
    if (!n && level == 0)
    {
        write(1, "0", 1);
        return (1);
    }
    else if (!n)
        return (0);
    temp = n % 10;
    c = temp + 48;
    count = print_uint_max(n / 10, flag, level + 1);
    if (flag == 1)
        write(1, &c, 1);
    count++;
    return (count);
}

int     print_int_max(intmax_t n, int flag)
{
    intmax_t temp;
    char c;
    int count;
    if (!n)
        return (0);
    temp = n % 10;
    c = temp + 48;
    count = print_int_max(n / 10, flag);
    if (flag == 1)
        write(1, &c, 1);
    count++;
    return (count);
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
	if (flags[6] == 0 && flags[3] == 1)
	{
		write(1, "0x", 2);
		count += 2;
		while (count < flags[5] - len)
			count += write_and_increment('0');
		count += convert_to_hex(dec, 1);
	}
	else
	{
		while (count < flags[5] - len - 2)
			count += write_and_increment(' ');
		write(1, "0x", 2);
		count += 2;
		count += convert_to_hex(dec, 1);
	}
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
            count += format_p_right_helper_3(flags, dec, len);
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

int    format_d_left_helper_1(int flags[], intmax_t argument, int len)
{
    int count;

    count = format_d_sign(flags, &argument);
    if (count == 1) //which means we wrote something
    {
        while (count < flags[7] - len + 1)
            count += write_and_increment('0');
        count += print_uint_max(argument, 1, 0);
    }
    else
    {
        while (count < flags[7] - len)
            count += write_and_increment('0');
        count += print_uint_max(argument, 1, 0);
    }
    return (count);
}

int     format_d_left_helper_2(int flags[], intmax_t argument, int len)
{
    //len >= precision so precision is not considered
    //minw greatest
    int count;

    count = format_d_sign(flags, &argument);
    count += print_uint_max(argument, 1, 0);
    while (count < flags[5])
        count += write_and_increment(' ');
    return (count);
}

int     format_d_left_helper_3(int flags[], intmax_t argument, int len)
{
    //minw >= precision && minw >= len
    //precision > len
    int count;

    count = format_d_sign(flags, &argument);
    if (count == 1) //which means we wrote something
    {
        while (count < flags[7] - len + 1)
            count += write_and_increment('0');
        count += print_uint_max(argument, 1, 0);
    }
    else
    {
        while (count < flags[7] - len)
            count += write_and_increment('0');
        count += print_uint_max(argument, 1, 0);
    }
    while (count < flags[5])
        count += write_and_increment(' ');
    return (count);
}

int     format_d_left(int flags[], intmax_t argument, int len)
{
    int count;

    count = 0;
    if (len >= flags[5] && len >= flags[7])
    {
        count = format_d_sign(flags, &argument); //writes the sign if its there
        count += print_uint_max(argument, 1, 0);
    }
    else if (flags[7] >= flags[5] && flags[7] >= len)
        count += format_d_left_helper_1(flags, argument, len);
    else if (flags[5] >= flags[7] && flags[5] >= len)
    {
        if (len >= flags[7])
            count += format_d_left_helper_2(flags, argument, len);
        else
            count += format_d_left_helper_3(flags, argument, len);
    }
    return (count);
}

int     format_d_right_helper_1(int flags[], intmax_t argument, int len)
{
    printf("fdrh1\n");
    //precision greatest
    //minw ignored
    //for format d, if precision is the greatest, then really its just the same case
    //for both left and right, so simply call the one you wrote already
    return (format_d_left_helper_1(flags, argument, len));
}

int     format_d_right_helper_2(int flags[], intmax_t argument, int len)
{
    printf("fdrh2\n");
    //minw greatest
    //len >= precision so precision is ignored
    //must consider flags[3] since it could be zero padded
    int count;

    count = 0;
    if (flags[3] == 1 && flags[6] == 0 && flags[7] == 0)
    {
        count += format_d_sign(flags, &argument);
        while (count < flags[5] - len)
            count += write_and_increment('0');
        count += print_uint_max(argument, 1, 0);
    }
    else
    {
        while (count < flags[5] - len - 1)
            count += write_and_increment(' ');
        if (format_d_sign(flags, &argument) == 1)
            count += 1;
        else
            count += write_and_increment(' ');
        count += print_uint_max(argument, 1, 0);
    }
    return (count);
}

int     format_d_right_helper_3(int flags[], intmax_t argument, int len)
{
    printf("fdrh3\n");
    //minw greatest
    //precision > len
    int count;

    count = 0;
    while (count < flags[5] - flags[7] - 1)
        count += write_and_increment(' ');
    if (format_d_sign(flags, &argument) == 1)
        count += 1;
    else
        count += write_and_increment(' ');
    while (count < flags[5] - len)
        count += write_and_increment('0');
    count += print_uint_max(argument, 1, 0);
    return (count);
}

int     format_d_right(int flags[], intmax_t argument, int len)
{
    int count;

    count = 0;
    if (len >= flags[5] && len >= flags[7])
    {
        count = format_d_sign(flags, &argument); //writes the sign if its there
        count += print_uint_max(argument, 1, 0);
    }
    else if (flags[7] >= flags[5] && flags[7] >= len)
        count += format_d_right_helper_1(flags, argument, len); //maybe just switch to left one to save a function
    else if (flags[5] >= flags[7] && flags[5] >= len)
    {
        if (len >= flags[7])
            count += format_d_right_helper_2(flags, argument, len);
        else
            count += format_d_right_helper_3(flags, argument, len);
    }
    return (count);
}

int		format_d(int flags[], va_list args)
{
	int count;
	intmax_t argument;
	int len;

	count = 0;
	argument = get_int_arg(flags, args);
	len = get_int_len(argument);
	if (flags[1] == 1) //left align
		count = format_d_left(flags, argument, len);
	else
		count = format_d_right(flags, argument, len);
	return (count);
}

int     f_special_right(int flags[], intmax_t hold, int count)
{
    int temp;

    temp = 0;
    if (flags[3] && flags[0])
        count += write_and_increment('+');
    else if (flags[3] && hold < 0)
        count += write_and_increment('-');
    else if (flags[3] && flags[4])
        count += write_and_increment(' ');
    if (flags[6] == 0)
    {
        while (count < flags[5] - 9)
            count += (flags[3] == 1) ? write_and_increment('0') : write_and_increment(' ');
        if (!flags[3] && hold < 0)
            count += write_and_increment('-');
        else if (!flags[3] && flags[0])
            count += write_and_increment('+');
        else if (!flags[3] && flags[4])
            count += write_and_increment(' ');
        else
        {
            while (count < flags[5] - 8)
                count += (flags[3] == 1) ? write_and_increment('0') : write_and_increment(' ');
        }
        write(1, "0.", 2);
        count += 2;
        while (temp++ < 6 - get_int_len(hold))
            count += write_and_increment('0');
        count += print_int_max(hold, 1);
    }
    else if (flags[6] == 1) //no need for flags[6] == 1 flags[7] == 0 bc if prec is 0, then none of the numbers at the end are shown
    {
        while (count < flags[5] - (3 + flags[7]))
            count += (flags[3] == 1) ? write_and_increment('0') : write_and_increment(' ');
        if (!flags[3] && hold < 0)
            count += write_and_increment('-');
        else if (!flags[3] && flags[0])
            count += write_and_increment('+');
        else if (!flags[3] && flags[4])
            count += write_and_increment(' ');
        else
            if (count == 0 || count == 1)
            {
                while (count < flags[5] - flags[7] - 2)
                    count += (flags[3]) ? write_and_increment('0') : write_and_increment(' ');
            }
            else
                count += (flags[3] == 1) ? write_and_increment('0') : write_and_increment(' ');
        write(1, "0.", 2);
        count += 2;
        while (temp++ < flags[7] - get_int_len(hold))
            count += write_and_increment('0');
        count += (hold < 0) ? print_int_max(-hold, 1) : print_int_max(hold, 1);
    }
    return (count);
}

int     f_special_left(int flags[], intmax_t hold, int count)
{
    printf("fsl\n");
    int temp;

    temp = 0;
    count += format_d_sign(flags, &hold);
    write(1, "0.", 2);
    count += 2;
    while (temp++ < flags[7] - get_int_len(hold))
        count += write_and_increment('0');
    count += print_int_max(hold, 1);
    while (count < flags[5])
        count += write_and_increment(' ');
    return (count);
}

int     format_f_special(int flags[], long double argument, int count)
{
    intmax_t hold;

    if (flags[6] == 0)
        hold = get_prec_num_f(argument, 6);
    else if (flags[6] == 1 && flags[7] == 0)
        hold = (intmax_t)argument;
    else
        hold = get_prec_num_f(argument, flags[7]);
    if (flags[1] == 1)
        return (f_special_left(flags, hold, count));
    else
        return (f_special_right(flags, hold, count));
}

int     format_f_zero_left(int flags[], int count, long double arg)
{
    if (flags[0] == 1)
        count += write_and_increment('+');
    else if (arg < 0)
        count += write_and_increment('-');
    else if (flags[4] == 1)
        count += write_and_increment(' ');
    if (flags[6] == 0) //precision not specified, so automatically given to be 6
    {
        write(1, "0.000000", 8);
        count += 8;
        while (count < flags[5])
            count += write_and_increment(' ');
    }
    else if (flags[6] == 1 && flags[7] == 0)
    {
        count += write_and_increment('0');
        while (count < flags[5])
            count += write_and_increment(' ');
    }
    else if (flags[6] == 1)
    {
        write(1, "0.", 2);
        count += 2;
        while (flags[7]--)
            count += write_and_increment('0');
        while (count < flags[5])
            count += write_and_increment(' ');
    }
    return (count);
}

int     format_f_zero_right(int flags[], int count, long double arg)
{
    if (arg < 0 && flags[3])
        count += write_and_increment('-');
    else if (flags[3] && flags[0])
        count += write_and_increment('+');
    else if (flags[4] == 1 && flags[3])
        count += write_and_increment(' ');
    if (flags[6] == 0) // precision not specified so automatically given to be 6
    {
        while (count < flags[5] - 9)
            count += (flags[3] == 1) ? write_and_increment('0') : write_and_increment(' ');
        if (arg < 0 && !flags[3])
            count += write_and_increment('-');
        else if (flags[0] && !flags[3])
            count += write_and_increment('+');
        else if (flags[4] && !flags[3])
            count += write_and_increment(' ');
        while (count < flags[5] - 8)
            count += (flags[3] == 1) ? write_and_increment('0') : write_and_increment(' ');
        write(1, "0.000000", 8);
        count += 8;
    }
    else if (flags[6] == 1 && flags[7] == 0)
    {
        while (count < flags[5] - 2)
            count += (flags[3] == 1) ? write_and_increment('0') : write_and_increment(' ');
        if (!flags[3] && flags[0])
            count += write_and_increment('-');
        else if (arg < 0 && !flags[3])
            count += write_and_increment('+');
        else if (flags[4] == 1 && !flags[3])
            count += write_and_increment(' ');
        while (count < flags[5] - 1)
            count += (flags[3] == 1) ? write_and_increment('0') : write_and_increment(' ');
        count += write_and_increment('0');
    }
    else if (flags[6] == 1)
    {
        while (count < flags[5] - (3 + flags[7]))
            count += (flags[3] == 1) ? write_and_increment('0') : write_and_increment(' ');
        if (!flags[3] && flags[0])
            count += write_and_increment('-');
        else if (arg < 0 && !flags[3])
            count += write_and_increment('+');
        else if (flags[4] == 1 && !flags[3])
            count += write_and_increment(' ');
        else
        {
            if (count == 0 || count == 1)
            {
                while (count < flags[5] - flags[7] - 2)
                    count += (flags[3]) ? write_and_increment('0') : write_and_increment(' ');
            }
            else
                count += (flags[3] == 1) ? write_and_increment('0') : write_and_increment(' ');
        }
        write(1, "0.", 2);
        count += 2;
        while (flags[7]--)
            count += write_and_increment('0');
    }
    return (count);
}

int     f_test_zero(int flags[], long double argument)
{
    intmax_t hold;

    if (flags[6] == 0)
        hold = get_prec_num_f(argument, 6);
    else if (flags[6] == 1 && flags[7] == 0)
        hold = (intmax_t)argument;
    else
        hold = get_prec_num_f(argument, flags[7]);
    return (hold == 0) ? 0 : 1;
}

int     format_f_zero(int flags[], long double arg)
{
    int count;

    count = 0;
    if (flags[1] == 1) //left justify
        count += format_f_zero_left(flags, count, arg);
    else
        count += format_f_zero_right(flags, count, arg);
    return (count);
}

int     format_f_left(int flags[], char *f_string, long double arg)
{
    int count;
    intmax_t hold;

    hold = (intmax_t)arg;
    count += format_d_sign(flags, &hold);
    ft_putstr(f_string);
    count += ft_strlen(f_string);
    while (count < flags[5])
        count += write_and_increment(' ');
    return (count);
}

int     format_f_right(int flags[], char *f_string, int len, long double arg)
{
    int count;

    count = 0;
    if (flags[3] == 1) //0 pad
    {
        if (arg < 0)
            count += write_and_increment('-');
        else if (flags[0])
            count += write_and_increment('+');
        else if (flags[4])
            count += write_and_increment(' ');
        while (count < flags[5] - len)
            count += (flags[3] == 1) ? write_and_increment('0') : write_and_increment(' ');
    }
    else
    {
        while (count < flags[5] - len - 1)
            count += write_and_increment(' ');
        if (arg < 0)
            count += write_and_increment('-');
        else if (flags[0])
            count += write_and_increment('+');
        else if (flags[4])
            count += write_and_increment(' ');
        while (count < flags[5] - len)
            count += write_and_increment(' ');
    }
    ft_putstr(f_string);
    count += ft_strlen(f_string);
    return (count);
}

int     format_f_string(int flags[], long double argument, char **f_string)
{
    int len;

    if (flags[6] == 0)
        *f_string = build_f_string(argument, 6);
    else if (flags[6] == 1 && flags[7] == 0)
        *f_string = build_f_string(argument, 0);
    else
        *f_string = build_f_string(argument, flags[7]);
    len = ft_strlen(*f_string);
    return (len);
}

int		format_f(int flags[], va_list args)
{
	int count;
	int len;
	long double argument;
	char *temp;

	argument = get_float_arg(flags, args);
	count = 0;
	if (argument == 0 || f_test_zero(flags, argument) == 0) //0 case or truncated string would round to zero
		return (format_f_zero(flags, argument));
	if ((argument < 1 && argument > 0) || (argument < 0 && argument > -1)) //self explanatory
		return (format_f_special(flags, argument, count));
	len = format_f_string(flags, argument, &temp); //sets up temp string, returns length of created string
    if (flags[1] == 1)
		count += format_f_left(flags, temp, argument);
	else
		count += format_f_right(flags, temp, len, argument);
	free(temp);
	return (count);
}


int		format_i(int flags[], va_list args)
{
	return(format_d(flags, args));
}

int     format_o_left_helper_1(int flags[], uintmax_t argument, int len)
{
    int count;

    count = 0;
    while (count < flags[7] - len)
        count += write_and_increment('0');
    count += (argument > 0) ? convert_to_octal(argument, 1) : write_and_increment('0');
    return (count);
}

int     format_o_left_helper_2(int flags[], uintmax_t argument, int len)
{
    //minw >= both
    // len >= precision
    int count;

    count = 0;
    if (flags[7] == 0 && flags[6] == 1)
        count += (argument > 0) ? convert_to_octal(argument, 1) : write_and_increment(' ');
    else
        count += (argument > 0) ? convert_to_octal(argument, 1) : write_and_increment('0');
    while (count < flags[5])
        count += write_and_increment(' ');
    return (count);
}

int     format_o_left_helper_3(int flags[], uintmax_t argument, int len)
{
    //minw >= both
    //precision > len
    int count;

    count = 0;
    while (count < flags[7] - len)
        count += write_and_increment('0');
    count += convert_to_octal(argument, 1);
    while (count < flags[5])
        count += write_and_increment(' ');
    return (count);
}

int     format_o_left(int flags[], uintmax_t argument, int len)
{
    int count;

    count = 0;
    if (len >= flags[5] && len >= flags[7])
    {
        if (flags[5] == 0 && flags[6] == 1 && flags[7] == 0 && argument == 0)
            count += 0;
        else if (flags[7] == 0 && flags[6] == 1)
            count += (argument > 0) ? convert_to_octal(argument, 1) : write_and_increment(' ');
        else
            count += (argument > 0) ? convert_to_octal(argument, 1) : write_and_increment('0');
    }
    else if (flags[7] >= flags[5] && flags[7] >= len)
        count += format_o_left_helper_1(flags, argument, len);
    else if (flags[5] >= len && flags[5] >= flags[7])
    {
        if (len >= flags[7])
            count += format_o_left_helper_2(flags, argument, len);
        else
            count += format_o_left_helper_3(flags, argument, len);
    }
    return (count);
}

int     format_o_right_helper_1(int flags[], uintmax_t argument, int len)
{
    //precision greatest
    printf("forh1\n");
    int count;

    count = 0;
    while (count < flags[7] - len)
        count += write_and_increment('0');
    count += (argument > 0) ? convert_to_octal(argument, 1) : write_and_increment('0');
    return (count);
}

int     format_o_right_helper_2(int flags[], uintmax_t argument, int len)
{
    //minw greatest
    //len >= precision
    printf("forh2\n");
    int count;

    count = 0;
    if (flags[6] == 0 && flags[3] == 1)
    {
        while (count < flags[5] - len)
            count += write_and_increment('0');
        if (flags[7] == 0 && flags[6] == 1)
            count += (argument > 0) ? convert_to_octal(argument, 1) : write_and_increment(' ');
        else
            count += (argument > 0) ? convert_to_octal(argument, 1) : write_and_increment('0');
    }
    else
    {
        while (count < flags[5] - len)
            count += write_and_increment(' ');
        if (flags[7] == 0 && flags[6] == 1)
            count += (argument > 0) ? convert_to_octal(argument, 1) : write_and_increment(' ');
        else
            count += (argument > 0) ? convert_to_octal(argument, 1) : write_and_increment('0');
    }
    return (count);
}

int     format_o_right_helper_3(int flags[], uintmax_t argument, int len)
{
    //minw greatest
    // precision > len
    printf("forh3\n");
    int count;

    count = 0;
    while (count < flags[5] - flags[7])
        count += write_and_increment(' ');
    while (count < flags[5] - len)
        count += write_and_increment('0');
    count += (argument > 0) ? convert_to_octal(argument, 1) : write_and_increment('0');
    return (count);
}

int     format_o_right(int flags[], uintmax_t argument, int len)
{
    int count;

    count = 0;
    if (len >= flags[5] && len >= flags[7])
    {
        if (flags[5] == 0 && flags[6] == 1 && flags[7] == 0 && argument == 0)
            count += 0;
        else if (flags[7] == 0 && flags[6] == 1)
            count += (argument > 0) ? convert_to_octal(argument, 1) : write_and_increment(' ');
        else
            count += (argument > 0) ? convert_to_octal(argument, 1) : write_and_increment('0');
    }
    else if (flags[7] >= flags[5] && flags[7] >= len)
        count += format_o_right_helper_1(flags, argument, len);
    else if (flags[5] >= len && flags[5] >= flags[7])
    {
        if (len >= flags[7])
            count += format_o_right_helper_2(flags, argument, len);
        else
            count += format_o_right_helper_3(flags, argument, len);
    }
    return (count);
}

int		format_o(int flags[], va_list args)
{
	int count;
	uintmax_t argument;
	int len;

	count = 0;
	argument = (uintmax_t)get_int_arg(flags, args); //this might give you issues
	len = (argument > 0) ? convert_to_octal(argument, 0) : 1;
	if (flags[1] == 1) //left align
		count = format_o_left(flags, argument, len);
	else
		count = format_o_right(flags, argument, len);
	return (count);
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

int		format_s_left_helper_1(int flags[], char *temp, int len)
{
    printf("fslh1\n");
	int count;

	count = 0;
    if (flags[7] == 0 && flags[6] == 0)
    {
        write(1, temp, len);
        count += len;
    }
    else
    {
        write(1, temp, flags[7]);
        count += flags[7];
        while (count < flags[5])
            count += write_and_increment(' ');
    }
    return (count);
}

int		format_s_left_helper_2(int flags[], char *temp, int len)
{;
	int count;

	count = 0;
	write(1, temp, flags[7]); //write up to precision first
	count += flags[7];
	while (count < flags[5])
		count += write_and_increment(' ');
	return (count);
}

int		format_s_left_helper_3(int flags[], char *temp, int len)
{
    printf("fslh3\n");
	//precision greater than len so ignore
	int count;

	count = 0;
	write(1, temp, len);
	count += len;
	while (count < flags[5])
		count += write_and_increment(' ');
	return (count);
}

int		format_s_left(int flags[], char *temp, int len)
{
	int count;

	count = 0;
    if (len >= flags[5] && len >= flags[7])
		count += format_s_left_helper_1(flags, temp, len);
	else if (flags[5] >= len && flags[5] >= flags[7])
	{
		if (len >= flags[7] && flags[7] > 0)
			count += format_s_left_helper_2(flags, temp, len);
		else
			count += format_s_left_helper_3(flags, temp, len); //precision ignored since greater than len

	}
	else if (flags[7] >= len && flags[7] >= flags[5]) //precision ignored
	{
		write(1, temp, len);
		count += len;
		while (count < flags[5])
			count += write_and_increment(' ');
	}
    return (count);
}

int     format_s_right_helper_1(int flags[], char *temp, int len)
{
    //case where length is the greatest of them all, so the only other
    //consideration is the precision
    int count;

    count = 0;
    if (flags[7] == 0 && flags[6] == 0)
    {
        write(1, temp, len);
        count += len;
    }
    else
    {
        while (count < flags[5] - flags[7])
            count += write_and_increment(' ');
        write(1, temp, flags[7]);
        count += flags[7];
    }
    return (count);
}

int     format_s_right_helper_2(int flags[], char *temp, int len)
{
    //case where length is greater than precision and minw greater than all
    //want to print out spaces until minw - precision then write precision worth of char
    //from temp
    int count;

    count = 0;
    while (count < flags[5] - flags[7])
        count += write_and_increment(' ');
    write(1, temp, flags[7]);
    count += flags[7];
    return (count);
}

int     format_s_right_helper_3(int flags[], char *temp, int len)
{
    //case where precision is ignored since it is larger
    int count;

    count = 0;
    while (count < flags[5] - len)
        count += write_and_increment(' ');
    write(1, temp, len);
    count += len;
    return (count);
}


int     format_s_right(int flags[], char *temp, int len)
{
    int count;

    count = 0;
    if (len >= flags[5] && len >= flags[7])
		count += format_s_right_helper_1(flags, temp, len);
	else if (flags[5] >= len && flags[5] >= flags[7])
	{
		if (len >= flags[7] && flags[7] > 0)
			count += format_s_right_helper_2(flags, temp, len);
		else
			count += format_s_right_helper_3(flags, temp, len); //precision ignored since greater than len

	}
	else if (flags[7] >= len && flags[7] >= flags[5]) //precision ignored
	{
		write(1, temp, len);
		count += len;
		while (count < flags[5])
			count += write_and_increment(' ');
	}
    return (count);
}

int		format_s(int flags[], va_list args) //first one you are working on
{
	int count;
	char *temp;
	int	len;

	temp = va_arg(args, char *);
	len = ft_strlen(temp);
    if (!flags[5] && !flags[7] && flags[6] == 1)
		return (0);
	else if (!flags[5] && !flags[7])
	{
		write(1, temp, len);
		return (len);
	}
	else
	{
		if (flags[1] == 1)
		    count = format_s_left(flags, temp, len); //non default behavior
		else
			count = format_s_right(flags, temp, len); //default behavior
	}
	return (count);
}

int     format_u_right_helper_1(int flags[], uintmax_t argument, int len)
{
    printf("furh1\n");
    int count;

    count = 0;
    while (count < flags[7] - len)
        count += write_and_increment('0');
    count += (argument > 0) ? print_uint_max(argument, 1, 0) : write_and_increment('0');
    return (count);
}

int     format_u_right_helper_2(int flags[], uintmax_t argument, int len)
{
    printf("furh2\n");
    int count;

    count = 0;
    if (flags[6] == 0 && flags[3] == 1)
    {
        while (count < flags[5] - len)
            count += write_and_increment('0');
        if (flags[7] > 0)
            count += (argument > 0) ? print_uint_max(argument, 1, 0) : write_and_increment('0');
        else
            count += (argument > 0) ? print_uint_max(argument, 1, 0) : write_and_increment(' ');
    }
    else
    {
        while (count < flags[5] - len)
            count += write_and_increment(' ');
        if (flags[7] == 0 && flags[6] == 1)
            count += (argument > 0) ? print_uint_max(argument, 1, 0) : write_and_increment(' ');
        else
            count += (argument > 0) ? print_uint_max(argument, 1, 0) : write_and_increment('0');
    }
    return (count);
}

int     format_u_right_helper_3(int flags[], uintmax_t argument, int len)
{
    printf("furh3\n");
    int count;

    count = 0;
    while (count < flags[5] - flags[7])
        count += write_and_increment(' ');
    while (count < flags[5] - len)
        count += write_and_increment('0');
    count += (argument > 0) ? print_uint_max(argument, 1, 0) : write_and_increment('0');
    return (count);
}

int     format_u_right(int flags[], uintmax_t argument, int len)
{
    int count;

    count = 0;
    if (len >= flags[5] && len >= flags[7])
    {
        if (flags[5] == 0 && flags[6] == 1 && flags[7] == 0  && argument == 0)
            count += 0;
        else if (flags[7] == 0 && flags[6] == 1)
            count += (argument > 0) ? print_uint_max(argument, 1, 0) : write_and_increment(' ');
        else
            count += (argument > 0) ? print_uint_max(argument, 1, 0) : write_and_increment('0');
    }
    else if (flags[7] >= flags[5] && flags[7] >= len)
        count += format_u_right_helper_1(flags, argument, len);
    else if (flags[5] >= len && flags[5] >= flags[7])
    {
        if (len >= flags[7])
            count += format_u_right_helper_2(flags, argument, len);
        else
            count += format_u_right_helper_3(flags, argument, len);
    }
    return (count);
}

int     format_u_left_helper_1(int flags[], uintmax_t argument, int len)
{
    printf("fulh1\n");
    int count;

    count = 0;
    while (count < flags[7] - len)
        count += write_and_increment('0');
    count += (argument > 0) ? print_uint_max(argument, 1, 0) : write_and_increment('0');
    return (count);
}

int     format_u_left_helper_2(int flags[], uintmax_t argument, int len)
{
    printf("fulh2\n");
    int count;

    count = 0;
    if (flags[7] == 0 && flags[6] == 1)
        count += (argument > 0) ? print_uint_max(argument, 1, 0) : write_and_increment(' ');
    else
        count += (argument > 0) ? print_uint_max(argument, 1, 0) : write_and_increment('0');
    while (count < flags[5])
        count += write_and_increment(' ');
    return (count);
}

int     format_u_left_helper_3(int flags[], uintmax_t argument, int len)
{
    int count;

    count = 0;
    while (count < flags[7] - len)
        count += write_and_increment('0');
    count += (argument > 0) ? print_uint_max(argument, 1, 0) : write_and_increment('0');
    while (count < flags[5])
        count += write_and_increment(' ');
    return (count);
}

int     format_u_left(int flags[], uintmax_t argument, int len)
{
    int count;

    count = 0;
    if (len >= flags[5] && len >= flags[7])
    {
        if (flags[5] == 0 && flags[6] == 1 && flags[7] == 0 && argument == 0)
            count += 0;
        else if (flags[7] == 0 && flags[6] == 1)
            count += (argument > 0) ? print_uint_max(argument, 1, 0) : write_and_increment(' ');
        else
            count += (argument > 0) ? print_uint_max(argument, 1, 0) : write_and_increment('0');
    }
    else if (flags[7] >= flags[5] && flags[7] >= len)
        count += format_u_left_helper_1(flags, argument, len);
    else if (flags[5] >= len && flags[5] >= flags[7])
    {
        if (len >= flags[7])
            count += format_u_left_helper_2(flags, argument, len);
        else // minw >= precision > len
            count += format_u_left_helper_3(flags, argument, len);
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

int     format_x_left_helper_1(int flags[], uintmax_t argument, int len)
{
    int count;

    count = 0;
    while (count < flags[7] - len)
        count += write_and_increment('0');
    count += (argument > 0) ? convert_to_hex(argument, 1) : write_and_increment('0');
    return (count);
}

int     format_x_left_helper_2(int flags[], uintmax_t argument, int len)
{
    //minw >= both
    // len >= precision
    int count;

    count = 0;
    if (flags[7] == 0 && flags[6] == 1)
        count += (argument > 0) ? convert_to_hex(argument, 1) : write_and_increment(' ');
    else
        count += (argument > 0) ? convert_to_hex(argument, 1) : write_and_increment('0');
    while (count < flags[5])
        count += write_and_increment(' ');
    return (count);
}

int     format_x_left_helper_3(int flags[], uintmax_t argument, int len)
{
     //minw >= both
    //precision > len
    int count;

    count = 0;
    while (count < flags[7] - len)
        count += write_and_increment('0');
    count += (argument > 0) ? convert_to_hex(argument, 1) : write_and_increment('0');
    while (count < flags[5])
        count += write_and_increment(' ');
}

int     format_x_right_helper_1(int flags[], uintmax_t argument, int len)
{
    int count;

    count = 0;
    while (count < flags[7] - len)
        count += write_and_increment('0');
    count += (argument > 0) ? convert_to_hex(argument, 1) : write_and_increment('0');
    return (count);
}

int     format_x_left(int flags[], uintmax_t argument, int len)
{
    int count;

    count = 0;
    if (len >= flags[5] && len >= flags[7])
    {
        if (flags[5] == 0 && flags[6] == 1 && flags[7] == 0 && argument == 0)
            count += 0;
        else if (flags[7] == 0 && flags[6] == 1)
            count += (argument > 0) ? convert_to_hex(argument, 1) : write_and_increment(' ');
        else
            count += (argument > 0) ? convert_to_hex(argument, 1) : write_and_increment('0');
    }
    else if (flags[7] >= flags[5] && flags[7] >= len)
        count += format_x_left_helper_1(flags, argument, len);
    else if (flags[5] >= len && flags[5] >= flags[7])
    {
        if (len >= flags[7])
            count += format_x_left_helper_2(flags, argument, len);
        else
            count += format_x_left_helper_3(flags, argument, len);
    }
    return (count);
}

int     format_x_right_helper_2(int flags[], uintmax_t argument, int len)
{
    int count;

    count = 0;
    if (flags[6] == 0 && flags[3] == 1)
    {
        while (count < flags[5] - len)
            count += write_and_increment('0');
        if (flags[7] == 0 && flags[6] == 1)
            count += (argument > 0) ? convert_to_hex(argument, 1) : write_and_increment(' ');
        else
            count += (argument > 0) ? convert_to_hex(argument, 1) : write_and_increment('0');
    }
    else
    {
        while (count < flags[5] - len)
            count += write_and_increment(' ');
        if (flags[7] == 0 && flags[6] == 1)
            count += (argument > 0) ? convert_to_hex(argument, 1) : write_and_increment(' ');
        else
            count += (argument > 0) ? convert_to_hex(argument, 1) : write_and_increment('0');
    }
    return (count);
}

int     format_x_right_helper_3(int flags[], uintmax_t argument, int len)
{
    //minw greatest
    // precision > len
    int count;

    count = 0;
    while (count < flags[5] - flags[7])
        count += write_and_increment(' ');
    while (count < flags[5] - len)
        count += write_and_increment('0');
    count += (argument > 0) ? convert_to_hex(argument, 1) : write_and_increment('0');
    return (count);
}

int     format_x_right(int flags[], uintmax_t argument, int len)
{
    int count;

    count = 0;
    if (len >= flags[5] && len >= flags[7])
    {
        if (flags[5] == 0 && flags[6] == 1 && flags[7] == 0 && argument == 0)
            count += 0;
        else if (flags[7] == 0 && flags[6] == 1)
            count += (argument > 0) ? convert_to_hex(argument, 1) : write_and_increment(' ');
        else
            count += (argument > 0) ? convert_to_hex(argument, 1) : write_and_increment('0');
    }
    else if (flags[7] >= flags[5] && flags[7] >= len)
        count += format_x_right_helper_1(flags, argument, len);
    else if (flags[5] >= len && flags[5] >= flags[7])
    {
        if (len >= flags[7])
            count += format_x_right_helper_2(flags, argument, len);
        else
            count += format_x_right_helper_3(flags, argument, len);
    }
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

int     format_x_upper_right_helper_1(int flags[], uintmax_t argument, int len)
{
    printf("fxurh1\n");
    int count;

    count = 0;
    while (count < flags[7] - len)
        count += write_and_increment('0');
    count += (argument > 0) ? convert_to_hex_upper(argument, 1) : write_and_increment('0');
    return (count);
}

int     format_x_upper_right_helper_2(int flags[], uintmax_t argument, int len)
{
    printf("fxurh2\n");
    int count;

    count = 0;
    if (flags[6] == 0 && flags[3] == 1)
    {
        while (count < flags[5] - len)
            count += write_and_increment('0');
        if (flags[7] == 0 && flags[6] == 1)
            count += (argument > 0) ? convert_to_hex_upper(argument, 1) : write_and_increment(' ');
        else
            count += (argument > 0) ? convert_to_hex_upper(argument, 1) : write_and_increment('0');
    }
    else
    {
        while (count < flags[5] - len)
            count += write_and_increment(' ');
        if (flags[7] == 0 && flags[6] == 1)
            count += (argument > 0) ? convert_to_hex_upper(argument, 1) : write_and_increment(' ');
        else
            count += (argument > 0) ? convert_to_hex_upper(argument, 1) : write_and_increment('0');
    }
    return (count);
}

int     format_x_upper_right_helper_3(int flags[], uintmax_t argument, int len)
{
    printf("fxurh3\n");
    //minw greatest
    // precision > len
    int count;

    count = 0;
    while (count < flags[5] - flags[7])
        count += write_and_increment(' ');
    while (count < flags[5] - len)
        count += write_and_increment('0');
    count += (argument > 0) ? convert_to_hex_upper(argument, 1) : write_and_increment('0');
    return (count);
}

int     format_x_upper_right(int flags[], uintmax_t argument, int len)
{
    printf("fxur\n");
    int count;

    count = 0;
    if (len >= flags[5] && len >= flags[7])
    {
        printf("in here X\n");
        if (flags[5] == 0 && flags[6] == 1 && flags[7] == 0 && argument == 0)
            count += 0;
        else if (flags[7] == 0 && flags[6] == 1)
            count += (argument > 0) ? convert_to_hex_upper(argument, 1) : write_and_increment(' ');
        else
            count += (argument > 0) ? convert_to_hex_upper(argument, 1) : write_and_increment('0');
    }
    else if (flags[7] >= flags[5] && flags[7] >= len)
        count += format_x_upper_right_helper_1(flags, argument, len);
    else if (flags[5] >= len && flags[5] >= flags[7])
    {
        if (len >= flags[7])
            count += format_x_upper_right_helper_2(flags, argument, len);
        else
            count += format_x_upper_right_helper_3(flags, argument, len);
    }
    return (count);
}

int     format_x_upper_left_helper_1(int flags[], uintmax_t argument, int len)
{
    printf("fxulh1\n");
    int count;

    count = 0;
    while (count < flags[7] - len)
        count += write_and_increment('0');
    count += (argument > 0) ? convert_to_hex_upper(argument, 1) : write_and_increment('0');
    return (count);
}

int     format_x_upper_left_helper_2(int flags[], uintmax_t argument, int len)
{
    printf("fxulh2\n");
    //minw >= both
    // len >= precision
    int count;

    count = 0;
    if (flags[7] == 0 && flags[6] == 1)
        count += (argument > 0) ? convert_to_hex_upper(argument, 1) : write_and_increment(' ');
    else
        count += (argument > 0) ? convert_to_hex_upper(argument, 1) : write_and_increment('0');
    while (count < flags[5])
        count += write_and_increment(' ');
    return (count);
}

int     format_x_upper_left_helper_3(int flags[], uintmax_t argument, int len)
{
    printf("fxulh3\n");
     //minw >= both
    //precision > len
    int count;

    count = 0;
    while (count < flags[7] - len)
        count += write_and_increment('0');
    count += (argument > 0) ? convert_to_hex_upper(argument, 1) : write_and_increment('0');
    while (count < flags[5])
        count += write_and_increment(' ');
    return (count);
}


int     format_x_upper_left(int flags[], uintmax_t argument, int len)
{
    printf("fxul\n");
    int count;

    count = 0;
    if (len >= flags[5] && len >= flags[7])
    {
        printf("in fxul first\n");
        if (flags[5] == 0 && flags[6] == 1 && flags[7] == 0 && argument == 0)
            count += 0;
        else if (flags[7] == 0 && flags[6] == 1)
            count += (argument > 0) ? convert_to_hex_upper(argument, 1) : write_and_increment(' ');
        else
            count += (argument > 0) ? convert_to_hex_upper(argument, 1) : write_and_increment('0');
    }
    else if (flags[7] >= flags[5] && flags[7] >= len)
        count += format_x_upper_left_helper_1(flags, argument, len);
    else if (flags[5] >= len && flags[5] >= flags[7])
    {
        if (len >= flags[7])
            count += format_x_upper_left_helper_2(flags, argument, len);
        else
            count += format_x_upper_left_helper_3(flags, argument, len);
    }
    return (count);
}

int		format_x_upper(int flags[], va_list args)
{
	int count;
	uintmax_t argument;
	int len;

	count = 0;
	argument = (uintmax_t)get_int_arg(flags, args);
	len = convert_to_hex_upper(argument, 0);
	if (flags[1] == 1)
		count = format_x_upper_left(flags, argument, len);
	else
		count = format_x_upper_right(flags, argument, len);
	return (count);
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
    float testnorm = 45.566;
    float testzero = 0.00;
    float testspec = 0.18344;
    int check1 = 0;
    //printf("check1 real: %d\n", check1);
    //ft_printf("check1 mine: %d\n", check1);
    printf("format string %%10f\n");
    int i = printf("test norm: |%-f| <------ real", testnorm);
    printf("\n");
    int j = ft_printf("test norm: |%-f| <------ mine", testnorm);
    printf("\n");
    printf("%d =? %d\n", i, j);
    int k = printf("test zero: |%+ 0.f| <------ real", testzero);
    printf("\n");
    int l = ft_printf("test zero: |%+ 0.f| <------ mine", testzero);
    printf("\n");
    printf("%d =? %d\n", k, l);
    int m = printf("test spec: |% 7.4f| <------ real", testspec);
    printf("\n");
    int n = ft_printf("test spec: |% 7.4f| <------ mine", testspec);
    printf("\n");
    printf("%d =? %d\n", m, n);
    return (0);
}

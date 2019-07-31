/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_s_helpers_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 14:32:02 by mqian             #+#    #+#             */
/*   Updated: 2019/07/31 16:24:35 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_s_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 16:47:11 by mqian             #+#    #+#             */
/*   Updated: 2019/08/19 15:18:10 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		format_s_left(int flags[], char *temp, int len)
{
	int count;

	count = 0;
    if (len >= flags[5] && len >= flags[7])
		count += format_s_left_helper_1(flags, temp, len);
	else if (flags[5] >= len && flags[5] >= flags[7])
	{
		if (len >= flags[7] && flags[7] > 0)
			count += format_s_left_helper_2(flags, temp);
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

int		format_s_left_helper_1(int flags[], char *temp, int len)
{
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

int		format_s_left_helper_2(int flags[], char *temp)
{
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
	//precision greater than len so ignore
	int count;

	count = 0;
	write(1, temp, len);
	count += len;
	while (count < flags[5])
		count += write_and_increment(' ');
	return (count);
}
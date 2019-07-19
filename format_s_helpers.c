/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_s_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 16:47:11 by mqian             #+#    #+#             */
/*   Updated: 2019/07/18 19:28:18 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		format_s_left(int flags[], char *temp, int len)
{
	int 	count

	count = 0;
	if (flags[6] > 0 && flags[6] < len)
	{
		while (flags[6]-- > 0)
		{
			putchar(*temp);
			count++;
			temp++;
		}
		while (count < flags[5])
		{
		    count++;
			putchar(' ');
		}
	}
	else //no consideration for precision, as long as minw is greater than len, pad til minw, else, just write out the string
		count = format_s_left_helper(flags, temp, len);
	return (count);
}

int		format_s_left_helper(int flags[], char *temp, int len)
{
	int		count;

	count = 0;
	while (count < len) //putchar til end of string
	{
		count++;
		ft_putchar(*temp);
		temp++;
	}
	while (count < flags[5]) //pad down spaces until end of minw 
	{
		ft_putchar(' ');
		count++;
	}
	return (count);
}

int		format_s_right(int flags[], char *temp, int len)
{
	int pad;
	int	count;

	pad = 0;
	count = 0;
	if (flags[6] > 0 && flags[6] =< len)
		count = format_s_right_helper(flags, temp, len);
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

int		format_s_right_helper(int flags[], char *temp, int len)
{
	int count;
	
	count = 0;
	if (flags[6] > flags[5]) //precision greater than minw, no need to justify
	{
		while (flags[6]-- > 0)
		{
			count++;
			write(1, temp++, 1);
			//temp++;
		}
	}
	else //precision not as great as minw, need to pad the left side with stuff
	{
		while (pad++ < flags[5] - flags[6])
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
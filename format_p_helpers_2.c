/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_p_helpers_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 18:07:45 by Thunderpurt       #+#    #+#             */
/*   Updated: 2019/07/30 12:17:22 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// int     format_p_right_helper(int flags[], unsigned dec, int len)
// {
//     int count;

//     count = 0;
//     if (len + 2 > flags[5]) //since 0x
//     {
//         write(1, "0x", 2);
//         count +=2;
//         count += convert_to_hex(dec, 1);
//     }
//     else
//     {
//         while (count < (flags[5] - (len + 2)))
//         {
//             write(1, " ", 1);
//             count++;
//         }
//         write(1, "0x", 2);
//         count += 2;
//         count += convert_to_hex(dec, 1);
//     }
//     return (count);
// }

int     format_p_right_helper(int flags[], uintmax_t dec, int len)
{
    int count;

    count = 0;
    if (len >= flags[5] && len >= flags[7])
	{
		write(1, "0x", 2);
		count += 2;
        count += convert_to_hex(dec, 1);
	}
    else if (flags[7] >= flags[5] && flags[7] >= len)
	{
		write(1, "0x", 2);
		count += 2;
        count += format_p_right_helper_1(flags, dec, len);
	}
    else if (flags[5] >= len && flags[5] >= flags[7])
    {
        if (len >= flags[7])
            count += format_p_right_helper_2(flags, dec, len);
        else // minw >= precision > len
            count += format_p_right_helper_3(flags, dec, len);
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
		count += format_p_helper_1(flags, dec, len);
	}
	return (count);
}

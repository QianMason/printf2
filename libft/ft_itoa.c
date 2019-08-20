/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 19:22:27 by mqian             #+#    #+#             */
/*   Updated: 2019/03/14 18:46:07 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_numdigits(unsigned int n)
{
	int count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char		*ft_itoa(int n)
{
	unsigned int	num;
	int				count;
	int				sign;
	char			*new;

	sign = 1;
	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
		sign = -1;
	}
	num = (unsigned int)n;
	count = count + ft_numdigits(num);
	if (!(new = ft_strnew(sizeof(char) * count)))
		return (NULL);
	while (--count >= 0)
	{
		new[count] = (char)((num % 10) + 48);
		num = num / 10;
	}
	if (sign < 0)
		new[0] = '-';
	return (new);
}

/*
** converts an integer to an ascii representation of that number
** uses an unsigned int, a count to count number of digits in the
** number, a sign for positive or negatiev at the end, and a char *
** pointer to hold the new array
** first if n is less than zero, it increments the count by one
** (because '-' char) and then sets n to negative version of itself,
** and sign to -1;
** num gets assigned to n to handle integer overflow
** count gets assigned to whatever value it was before (possibly 0 or 1)
** and then adds it to the number of digits the integer is
** allocate space for new string array (return null if allocation fails)
** use count to decrement and write from the back by using modulo to get
** the number in the back. then divide the number by 10 to get rid of
** that number
** at the end, if sign is less than zero, write in the last '-' char
** in the front.
** return string array
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqian <mqian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 14:28:57 by mqian             #+#    #+#             */
/*   Updated: 2019/04/16 20:04:50 by mqian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ret_string_delim(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (ft_strsub(s, 0, i));
}

char	*ret_remain_line(char *s, char c)
{
	int i;
	int j;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	j = i;
	while (s[i])
	{
		i++;
	}
	if (j == i)
		return (ft_strsub(s, j, 0));
	j++;
	return (ft_strsub(s, j, (i - j)));
}

int		read_helper(int ret, char *buff, char **filed, char **line)
{
	char *temp;
	char *temp2;

	buff[ret] = '\0';
	if (!*filed)
		*filed = ft_strnew(0);
	temp = ft_strjoin(*filed, buff);
	ft_memdel((void **)&*filed);
	*filed = temp;
	if (ft_strchr(*filed, '\n'))
	{
		*line = ret_string_delim(*filed, '\n');
		temp2 = ret_remain_line(*filed, '\n');
		ft_memdel((void **)&*filed);
		*filed = temp2;
		return (1);
	}
	return (0);
}

int		get_remain_lines(char **filed, char **line)
{
	char	*temp;
	char	*temp2;
	int		len;

	len = 0;
	if (ft_strchr(*filed, '\n'))
	{
		temp = ret_string_delim(*filed, '\n');
		temp2 = ret_remain_line(*filed, '\n');
		*line = temp;
		ft_memdel((void **)&*filed);
		*filed = temp2;
		return (1);
	}
	else
	{
		if (ft_strlen(*filed) > 0)
		{
			*line = ft_strdup(*filed);
			ft_memdel((void **)&*filed);
			return (1);
		}
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static char		*filed[5000];
	char			buff[BUFF_SIZE + 1];
	int				ret;

	if (fd < 0 || !line)
		return (-1);
	if (filed[fd])
		ft_memdel((void**)&*line);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (read_helper(ret, buff, &filed[fd], &*line))
			break ;
	}
	if (ret == 0 && filed[fd])
	{
		if (get_remain_lines(&filed[fd], &*line))
			return (1);
		else
			return (0);
	}
	if (ret == 0)
		return (0);
	return ((ret < 0) ? -1 : 1);
}

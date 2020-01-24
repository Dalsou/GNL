/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_gnl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoulqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 12:11:55 by afoulqui          #+#    #+#             */
/*   Updated: 2020/01/24 15:50:41 by afoulqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		free_and_return(char **str, int ret)
{
	if ((*str) && (ret == -1 || ret == 0 ))
	{
		free(*str);
		(*str) = NULL;
	}
	return (ret);
}

int		find_line(char **str, char **line)
{
	char 			*tmp;
	int				i;

	tmp = *str;
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\n')
		{
			if (i == 0)
			{
				if (!((*line) = ft_strdup("")))
					return (-1);
			}
			else
			{
				if (!((*line) = ft_substr(*str, 0, i)))
					return (-1);
			}
			if (!(tmp = ft_substr(*str, i + 1, ft_strlen(*str))))
				return (-1);
			free(*str);
			*str = tmp;
			return (1);
		}
		i++;
	}
	return (0);
}

int		check_error_and_str(char **str, char **line, int fd)
{
	int			ret;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	if (*str)
	{
		ret = find_line(str, line);
		return (ret);
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char 	*str;
	char			buff[BUFFER_SIZE + 1];
	int				ret;

	ret = check_error_and_str(&str, line, fd);
	if (ret == 0)
	{
		while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
		{
			buff[ret] = '\0';
			if (!(str = ft_strjoin(str, buff)))
				return (free_and_return(&str, -1));
			ret = find_line(&str, line);
			if (ret ==  1 || ret == -1)
				return (free_and_return(&str, ret));
		}
		if (!((*line) = ft_substr(str, 0, ft_strlen(str))))
			return (free_and_return(&str, -1));
	}
	return (free_and_return(&str, ret));
}

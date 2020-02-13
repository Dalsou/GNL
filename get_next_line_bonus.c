/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoulqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 16:54:19 by afoulqui          #+#    #+#             */
/*   Updated: 2020/01/29 13:25:56 by afoulqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		free_and_return(char **str, int ret)
{
	if ((*str) && (ret == -1 || ret == 0))
	{
		free(*str);
		(*str) = NULL;
	}
	return (ret);
}

int		find_line(char **str, char **line)
{
	int			i;
	char		*tmp;

	i = 0;
	tmp = *str;
	while (tmp[i])
	{
		if ((tmp[i]) == '\n')
		{
			if (i == 0)
				(*line) = ft_strdup("");
			else
				(*line) = ft_substr(*str, 0, i);
			if ((*line) == NULL)
				return (-1);
			if (!(tmp = ft_substr(*str, i + 1, ft_strlen(*str))))
				return (-1);
			free(*str);
			(*str) = tmp;
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
	if ((ret = read(fd, *str, 0) == -1))
		return (-1);
	if (*str)
	{
		ret = find_line(str, line);
		return (ret);
	}
	else
	{
		if (!(*str = ft_strdup("")))
			return (-1);
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static t_str	str[100];
	char			buff[BUFFER_SIZE + 1];
	int				ret;

	ret = check_error_and_str(&str[fd].s, line, fd);
	if (ret == 0)
	{
		while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
		{
			buff[ret] = '\0';
			if (!(str[fd].s = ft_strjoin(str[fd].s, buff)))
				return (free_and_return(&str[fd].s, -1));
			ret = find_line(&str[fd].s, line);
			if (ret == 1 || ret == -1)
				return (free_and_return(&str[fd].s, ret));
		}
		if (!((*line) = ft_substr(str[fd].s, 0, ft_strlen(str[fd].s))))
			return (free_and_return(&str[fd].s, -1));
	}
	return (free_and_return(&str[fd].s, ret));
}
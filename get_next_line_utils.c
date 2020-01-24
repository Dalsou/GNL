/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoulqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:22:35 by afoulqui          #+#    #+#             */
/*   Updated: 2020/01/24 16:03:44 by afoulqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	if (!s)
		return (NULL);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strdup(const char *s1)
{
	char*new;
	int i;
	int size;

	size = 0;
	size = ft_strlen((char *)s1);
	new = malloc(sizeof(char) * (size + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

static char	*fill_new(char *dst, char const *s2, unsigned int i, char *tmp)
{
	size_t			len;
	unsigned int	j;

	len = ft_strlen((char *)tmp);
	j = 0;
	while (j < len)
	{
		dst[i] = tmp[j];
		i++;
		j++;
	}
	if (tmp == s2)
	{
		dst[i] = '\0';
		return (dst);
	}
	return (fill_new(dst, s2, i, (char *)s2));
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char			*new;
	size_t			size;
	unsigned int	i;

	if (!s1)
	{
		if (!s2)
			return (NULL);
		return (ft_strdup((char *)s2));
	}
	if (!s2)
		return (NULL);
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	new = malloc(sizeof(char) * (size + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	fill_new(new, s2, i, (char *)s1);
	return (new);
}

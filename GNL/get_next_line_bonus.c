/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwarpath <kwarpath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:18:32 by kwarpath          #+#    #+#             */
/*   Updated: 2021/11/17 15:03:08 by kwarpath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	karetka(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*get_line(char **str)
{
	char	*txt;
	char	*line;

	if (karetka(*str) == -1)
	{
		line = ft_substr(*str, 0, ft_strlen(*str));
		free(*str);
		*str = NULL;
	}
	else
	{
		line = ft_substr(*str, 0, karetka(*str) + 1);
		txt = ft_substr(*str, karetka(*str) + 1, ft_strlen(*str));
		free(*str);
		*str = NULL;
		*str = ft_strdup(txt);
		free(txt);
		txt = NULL;
	}
	return (line);
}

static char	*rd_buffer(char **str, char *buffer, int fd)
{
	int		ret;
	char	*txt;

	if (karetka(*str) != -1)
		return (get_line(str));
	ret = read(fd, buffer, BUFFER_SIZE);
	if (ret <= 0)
	{
		if (**str)
			return (get_line(str));
		else
		{
			free(*str);
			*str = NULL;
			return (0);
		}
	}
	buffer[ret] = '\0';
	txt = ft_strjoin(*str, buffer);
	free(*str);
	*str = NULL;
	*str = ft_strdup(txt);
	free(txt);
	txt = NULL;
	return (rd_buffer(str, buffer, fd));
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*str[OPEN_MAX];

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || (read(fd, NULL, 0) < 0))
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	if (!str[fd])
		str[fd] = ft_strdup("");
	line = rd_buffer(&str[fd], buffer, fd);
	free(buffer);
	buffer = NULL;
	return (line);
}

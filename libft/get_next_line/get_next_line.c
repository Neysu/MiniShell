/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:22:02 by egibeaux          #+#    #+#             */
/*   Updated: 2025/02/25 22:35:17 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

static char	*read_line(int fd, char *line, char *buffer)
{
	ssize_t		bytes_read;
	char		*temp;

	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(line, buffer);
		free(line);
		if (!temp)
			return (NULL);
		line = temp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (bytes_read < 0 || (!bytes_read && !*line))
	{
		buffer[0] = '\0';
		free(line);
		return (NULL);
	}
	return (line);
}

static char	*trim_line(char *line, char *buffer)
{
	size_t		i;
	size_t		j;
	char		*trimmed_line;
	char		*newline_pos;

	if (!line && *buffer)
		line = ft_strndup(buffer, ft_strlen(buffer));
	if (!line)
		return (NULL);
	newline_pos = ft_strchr(line, '\n');
	if (!newline_pos)
	{
		buffer[0] = '\0';
		return (line);
	}
	i = newline_pos - line + 1;
	trimmed_line = ft_strndup(line, i);
	j = 0;
	while (line[i])
		buffer[j++] = line[i++];
	buffer[j] = '\0';
	free(line);
	return (trimmed_line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_strjoin("", buffer);
	line = read_line(fd, line, buffer);
	return (trim_line(line, buffer));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:03:42 by riyano            #+#    #+#             */
/*   Updated: 2024/12/22 16:18:44 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line_bonus.h"
#include <unistd.h>
#include <stdlib.h>

static char	*read_and_join(int fd, char *storage)
{
	char	*buf;
	char	*temp;
	int		bytes_read;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(storage, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buf[bytes_read] = '\0';
		temp = ft_strjoin(storage, buf);
		free(storage);
		storage = temp;
	}
	free(buf);
	return (storage);
}

static char	*extract_line(char *storage)
{
	char	*newline_pos;
	size_t	len;
	char	*line;

	newline_pos = ft_strchr(storage, '\n');
	if (!newline_pos)
		return (ft_strdup(storage));
	len = 0;
	while (storage[len])
	{
		if (newline_pos && (storage + len) >= newline_pos)
			break ;
		len++;
	}
	if (newline_pos)
		len++;
	line = ft_strndup(storage, len);
	return (line);
}

static char	*trim_storage(char *storage)
{
	char	*newline_pos;
	char	*remain;
	size_t	i;

	newline_pos = ft_strchr(storage, '\n');
	if (!newline_pos)
		return (NULL);
	i = (newline_pos + 1) - storage;
	remain = ft_strndup(storage + i, ft_strlen(storage + i));
	if (!remain || *remain == '\0')
	{
		free(remain);
		remain = NULL;
	}
	return (remain);
}

char	*get_next_line(int fd)
{
	static char	*buffers[FOPEN_MAX];
	char		*line;
	char		*temp;

	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buffers[fd] = read_and_join(fd, buffers[fd]);
	if (!buffers[fd])
		return (NULL);
	line = extract_line(buffers[fd]);
	temp = trim_storage(buffers[fd]);
	free(buffers[fd]);
	buffers[fd] = temp;
	return (line);
}
//
//#include <stdio.h>
//#include <fcntl.h>
//#include <string.h>
//int	main(int argc, char **argv)
//{
//	if (argc < 2)
//	{
//		printf("Usage: %s <filename>\n", argv[0]);
//		return 1;
//	}
//	int i = 1;
//	while (i < argc)
//	{
//		int fd = open(argv[i], O_RDONLY);
//		if (fd == -1)
//		{
//			perror("Error opening file");
//			return 1;
//		}
//		char *line;
//		while ((line = get_next_line(fd)) != NULL)
//		{
//			printf("Read line: %s", line);
//			free(line);
//		}
//		close(fd);
//		printf("\n----------------");
//		i++;
//	}
//	return 0;
//}
//

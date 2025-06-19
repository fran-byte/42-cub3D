/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:59:24 by frromero          #+#    #+#             */
/*   Updated: 2024/11/07 19:05:11 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This function reads from some files descriptors line by line. */
/* It stores leftover text in a static buffer between calls, */
/* handling partial lines across multiple reads. */
/* The `my_line` function extracts a full line */

#include "get_next_line_bonus.h"

char	*my_line(char *stored)
{
	int			i;
	char		*line;
	int			ln;

	i = 0;
	ln = 0;
	while (stored[ln] != '\n' && stored[ln] != '\0')
		ln++;
	if (*stored)
	{
		line = (char *)malloc((ln + 1) * sizeof(char) + 1);
		if (line == NULL)
			return (free(stored), NULL);
		while (i <= ln)
		{
			line[i] = stored[i];
			i++;
		}
		line[i] = '\0';
		return (line);
	}
	free(stored);
	return (NULL);
}

char	*re_adj_storage(char *stored)
{
	int		i;
	int		j;
	char	*swap_temp;

	i = 0;
	j = 0;
	while (stored[i] && stored[i] != '\n')
		i++;
	if (!stored[i++])
	{
		free(stored);
		return (NULL);
	}
	swap_temp = (char *)malloc((ft_strlen(stored) - i + 1) * sizeof(char));
	if (!swap_temp)
		return (NULL);
	while (stored[i])
		swap_temp[j++] = stored[i++];
	swap_temp[j] = '\0';
	free(stored);
	return (swap_temp);
}

char	*initialize_stored(char *stored, char *read_bff)
{
	if (!stored)
	{
		stored = malloc(1);
		if (!stored)
		{
			free(read_bff);
			return (NULL);
		}
		*stored = '\0';
	}
	return (stored);
}

char	*read_join(char *stored, int fd)
{
	ssize_t	bytes_read;
	char	*read_bff;

	read_bff = malloc(BUFFER_SIZE + 1);
	if (!read_bff)
		return (NULL);
	if (!stored)
		stored = initialize_stored(stored, read_bff);
	while (1)
	{
		bytes_read = read(fd, read_bff, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(read_bff);
			if (bytes_read == 0 && stored[0] != '\0')
				return (stored);
			return (free(stored), NULL);
		}
		read_bff[bytes_read] = '\0';
		stored = special_strjoin_(stored, read_bff);
		if (ft_strchr(read_bff, '\n'))
			break ;
	}
	free(read_bff);
	return (stored);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*stored[65536];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 65536)
		return (NULL);
	stored[fd] = read_join(stored[fd], fd);
	if (!stored[fd])
		return (NULL);
	line = my_line(stored[fd]);
	stored[fd] = re_adj_storage(stored[fd]);
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:32:50 by frromero          #+#    #+#             */
/*   Updated: 2025/04/08 19:15:52 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int open_file(char *arg, t_game *data)
{
	int fd;

	fd = open(arg, O_RDONLY);
	if (fd < 0)
	{
		report_err(OPEN_FILE_ERR);
		free_function(data);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
void free_split(char **grid_color)
{
	int i;

	if (!grid_color)
		return;
	i = 0;
	while (grid_color[i])
	{
		free(grid_color[i]);
		i++;
	}
	free(grid_color);
}

int is_numeric(const char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int count_char_in_str(const char *str, char c)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}
int ft_array_size(char **array)
{
	int count;

	count = 0;
	while (array && array[count])
		count++;
	return (count);
}

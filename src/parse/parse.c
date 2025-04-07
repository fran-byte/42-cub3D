/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 23:43:36 by frromero          #+#    #+#             */
/*   Updated: 2025/04/07 17:02:15 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void fill_map_file_grid(char *arg, t_game *data)
{
	char *line;
	int i;
	int fd;

	fd = open_file(arg, data);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		data->map.map_file[i] = malloc(ft_strlen(line) + 1);
		if (!data->map.map_file[i])
		{
			report_err(MALLOC_ERR);
			close(fd);
			free_function(data);
			exit(EXIT_FAILURE);
		}
		ft_strlcpy(data->map.map_file[i], line, ft_strlen(line) + 1);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}
void get_height_map(int fd, t_game *data)
{
	char *line;

	data->map.height_file = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		data->map.height_file++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void load_map(char *arg, t_game *data)
{
	int fd;

	fd = open_file(arg, data);
	get_height_map(fd, data);
	data->map.map_file = malloc(sizeof(char *) * data->map.height_file);
	if (!data->map.map_file)
	{
		report_err(MALLOC_ERR);
		close(fd);
		free_function(data);
		exit(EXIT_FAILURE);
	}
	fill_map_file_grid(arg, data);
	close(fd);
}

void parse_arg(char *arg, t_game *data)
{
	int ln;

	ln = ft_strlen(arg);
	if (!(arg[ln - 1] == 'b' && arg[ln - 2] == 'u' && arg[ln - 3] == 'c' && arg[ln - 4] == '.'))
	{
		report_err(SYNTAX_ERR);
		free_function(data);
		exit(EXIT_FAILURE);
	}
	load_map(arg, data);
	extract_map_data(data);
}

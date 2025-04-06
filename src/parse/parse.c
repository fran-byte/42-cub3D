/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 23:43:36 by frromero          #+#    #+#             */
/*   Updated: 2025/04/06 21:58:08 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void fill_map_file_grid(char *arg, t_game *data)
{
	char **grid;
	char *line;
	int i;
	int fd;

	fd = open_file(arg);
	i = 0;
	grid = data->map.map_file;
	line = get_next_line(fd);
	while (line != NULL)
	{
		grid[i] = malloc(ft_strlen(line) + 1);
		if (!grid[i])
		{
			report_err(MALLOC_ERR);
			close(fd);
			free_function(data);
			return;
		}
		ft_strlcpy(grid[i], line, ft_strlen(line) + 1);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}
void get_height_map(int fd, t_game *data)
{
	int height;
	char *line;

	height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	data->map.height_file = height;
	close(fd);
}

void load_map(char *arg, t_game *data)
{

	int height;
	int fd;

	fd = open_file(arg);
	get_height_map(fd, data);
	height = data->map.height_file;
	char **grid = malloc(sizeof(char *) * height);
	if (!grid)
	{
		report_err(MALLOC_ERR);
		close(fd);
		free_function(data);
		exit(EXIT_FAILURE);
	}
	data->map.map_file = grid;
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
		exit(EXIT_FAILURE);
	}
	load_map(arg, data);
	extract_map_data(data);
}

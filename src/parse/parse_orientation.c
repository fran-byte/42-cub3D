/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ORIENTATION_ERR.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:40:40 by frromero          #+#    #+#             */
/*   Updated: 2025/04/09 19:54:17 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void store_path(t_game *data, char *line, char **dest)
{
	char *path;

	path = ft_strtrim(line + 2, " \t");
	if (!path)
	{
		report_err(MALLOC_ERR);
		free_function(data);
		exit(EXIT_FAILURE);
	}
	if (access(path, R_OK) != 0)
	{
		free(path);
		report_err(TEXTURE_FILE_ERR);
		free_function(data);
		exit(EXIT_FAILURE);
	}
	*dest = path;
}

static void parse_line(t_game *data, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		store_path(data, line, &data->map.paths.north);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		store_path(data, line, &data->map.paths.south);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		store_path(data, line, &data->map.paths.west);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		store_path(data, line, &data->map.paths.east);
	else
	{
		report_err(ORIENTATION_ERR);
		free_function(data);
		exit(EXIT_FAILURE);
	}
}

void parse_ORIENTATION_ERR(t_game *data)
{
	if (!data->map.file[0] || !data->map.file[1] ||
		!data->map.file[2] || !data->map.file[3])
	{
		report_err(ORIENTATION_ERR);
		free_function(data);
		exit(EXIT_FAILURE);
	}
	parse_line(data, data->map.file[0]);
	parse_line(data, data->map.file[1]);
	parse_line(data, data->map.file[2]);
	parse_line(data, data->map.file[3]);
	if (!data->map.paths.north || !data->map.paths.south ||
		!data->map.paths.west || !data->map.paths.east)
	{
		report_err(ORIENTATION_ERR);
		free_function(data);
		exit(EXIT_FAILURE);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:19:35 by frromero          #+#    #+#             */
/*   Updated: 2025/04/09 19:29:18 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int calculate_map_height(t_game *data)
{
	int height;
	char **lines;

	height = 0;
	if (!data->map.file || !data->map.file[8])
		return (0);
	lines = data->map.file + 8;
	while (lines != NULL && *lines != NULL)
	{
		lines++;
		height++;
	}
	return (height);
}

static char **extract_map_lines(t_game *data)
{
	char **map;
	int i;

	i = 0;
	map = (char **)malloc(sizeof(char *) * (data->map.height_map + 1));
	if (!map)
		return (NULL);
	while (i < data->map.height_map)
	{
		map[i] = ft_strdup(data->map.file[8 + i]);
		if (!map[i])
		{
			free_split(map);
			return (NULL);
		}
		i++;
	}
	// map[height] = NULL;
	return (map);
}

void parse_map(t_game *data)
{
	data->map.height_map = calculate_map_height(data);
	if (data->map.height_map == 0)
	{
		report_err(MAP_VOID);
		free_function(data);
		exit(EXIT_FAILURE);
	}
	data->map.map = extract_map_lines(data);
	if (!data->map.map)
	{
		report_err(MAP_VOID);
		free_function(data);
		exit(EXIT_FAILURE);
	}
	parse_items_map(data);
	parse_validate_map(data);
	// store_orientation_sprites(data);
	//  store_colors(data);
}

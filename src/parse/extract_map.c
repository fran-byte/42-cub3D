/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:40:40 by frromero          #+#    #+#             */
/*   Updated: 2025/04/07 17:03:27 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void parse_orientation(t_game *data)
{
	char **orient;
	int i;
	int j;
	int valid;
	const char *prefixes[] = {"NO", "SO", "WE", "EA"};

	i = 0;
	orient = data->map.map_file;
	valid = 1;
	while (i < 4 && valid)
	{
		j = -1;
		valid = 0;
		while (++j < 4 && !valid)
		{
			if (orient[i][0] == prefixes[j][0] && orient[i][1] == prefixes[j][1] && (orient[i][2] == ' ' || orient[i][2] == '\t'))
				valid = 1;
		}
		if (!valid)
		{
			report_err(MAP_FORMAT);
			free_function(data);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void extract_map_data(t_game *data)
{
	parse_orientation(data);
	// parse_color(data);
	// parse_map(data);
}

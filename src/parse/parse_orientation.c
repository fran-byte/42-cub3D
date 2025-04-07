/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_orientation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:40:40 by frromero          #+#    #+#             */
/*   Updated: 2025/04/07 19:43:26 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void parse_path_orientation(t_game *data)
{
	char **path_block;
	int i;

	i = 0;
	path_block = data->map.file;
	while (i < 4)
	{
		if (strlen(path_block[i]) < 3)
		{
			report_err(TEXTURE_FILE);
			free_function(data);
			exit(EXIT_FAILURE);
		}
		if (access((path_block[i] + 3), R_OK) != 0)
		{
			report_err(TEXTURE_FILE);
			free_function(data);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void parse_cardinals(t_game *d)
{
	int i;
	int j;
	int valid;
	const char *p[] = {"NO", "SO", "WE", "EA"};

	i = 0;
	valid = 1;
	while (i < 4 && valid)
	{
		j = -1;
		valid = 0;
		while (++j < 4 && !valid)
		{
			if (d->map.file[i][0] == p[j][0] && d->map.file[i][1] == p[j][1] && (d->map.file[i][2] == ' ' || d->map.file[i][2] == '\t'))
				valid = 1;
		}
		if (!valid)
		{
			report_err(ORIENTATION);
			free_function(d);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void parse_orientation(t_game *data)
{
	parse_cardinals(data);
	parse_path_orientation(data);
}

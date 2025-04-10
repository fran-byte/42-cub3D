#include "../../include/cub3d.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:37:27 by frromero          #+#    #+#             */
/*   Updated: 2025/04/08 17:25:03 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void is_numeric_grid(t_game *data, char **grid_color)
{
	int i;

	i = 0;
	while (grid_color[i])
	{
		if (!is_numeric(grid_color[i]))
		{
			free_split(grid_color);
			report_err(FORMAT_COLOR_ERR);
			free_function(data);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void exit_error_color(t_game *data, char **grid)
{
	if (grid)
		free_split(grid);
	report_err(FORMAT_COLOR_ERR);
	free_function(data);
	exit(EXIT_FAILURE);
}

static void parse_color_line(t_game *data, char *line)
{
	char **rgb;
	int r;
	int g;
	int b;

	r = 0;
	g = 0;
	b = 0;
	rgb = ft_split(line + 2, ',');
	if (!rgb || ft_array_size(rgb) != 3)
		exit_error_color(data, rgb);
	is_numeric_grid(data, rgb);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		exit_error_color(data, rgb);
	free_split(rgb);
}

void parse_colors(t_game *data)
{

	if (!data->map.file[5] || !data->map.file[6])
		exit_error_color(data, NULL);
	if (data->map.file[5][0] == 'C' && data->map.file[6][0] == 'F' && data->map.file[6][1] == ' ')
		parse_color_line(data, data->map.file[6]);
	else if (data->map.file[5][0] == 'F' && data->map.file[6][0] == 'C' && data->map.file[6][1] == ' ')
		parse_color_line(data, data->map.file[6]);
	else
		exit_error_color(data, NULL);
	if ((count_char_in_str(data->map.file[5] + 2, ',') > 2) || (count_char_in_str(data->map.file[6] + 2, ',') > 2))
		exit_error_color(data, NULL);
}

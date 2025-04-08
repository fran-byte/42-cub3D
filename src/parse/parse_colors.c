/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:37:27 by frromero          #+#    #+#             */
/*   Updated: 2025/04/08 12:07:08 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int ft_array_size(char **array)
{
	int count;

	count = 0;
	while (array && array[count])
		count++;
	return (count);
}

void parse_colors(t_game *data)
{
	int i;
	int j;
	char **grid_color;
	int valor;

	if (!data->map.file[5] || !data->map.file[6] ||
		(ft_strlen(data->map.file[5]) < 4 || ft_strlen(data->map.file[6]) < 4) ||
		!((data->map.file[5][0] == 'C' && data->map.file[6][0] == 'F') ||
		  (data->map.file[5][0] == 'F' && data->map.file[6][0] == 'C')))
	{
		report_err(FORMAT_COLOR);
		free_function(data);
		exit(EXIT_FAILURE);
	}

	i = 5;
	while (i < 7)
	{
		grid_color = ft_split(data->map.file[i] + 2, ',');
		if (!grid_color || ft_array_size(grid_color) != 3)
		{
			report_err(FORMAT_COLOR);
			free_split(grid_color);
			free_function(data);
			exit(EXIT_FAILURE);
		}

		j = 0;
		while (j < 3)
		{
			valor = ft_atoi(grid_color[j]);
			if (valor < 0 || valor > 255)
			{
				report_err(FORMAT_COLOR);
				free_split(grid_color);
				free_function(data);
				exit(EXIT_FAILURE);
			}
			j++;
		}
		free_split(grid_color);
		i++;
	}
}

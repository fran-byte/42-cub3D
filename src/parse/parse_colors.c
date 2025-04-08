/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:37:27 by frromero          #+#    #+#             */
/*   Updated: 2025/04/08 10:34:46 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void parse_colors(t_game *data)
{
	int i;
	int j;
	char **grid_color;
	int valor;

	i = 0;
	valor = -1;
	if (!(data->map.file[5][0] == 'C' && data->map.file[6][0] == 'F') || (data->map.file[5][0] == 'F' && data->map.file[6][0] == 'C'))
	{
		report_err(FORMAT_COLOR);
		free_function(data);
		exit(EXIT_FAILURE);
	}
	i = 5;
	while (i < 7)
	{
		j = 0;
		while (j < 3)
		{
			grid_color = ft_split(data->map.file[i] + 2, ',');
			valor = ft_atoi(grid_color[j]);
			if (valor > 255 || valor < 0 || grid_color[3])
			{
				report_err(FORMAT_COLOR);
				free_split(grid_color);
				free_function(data);
				exit(EXIT_FAILURE);
			}
			free_split(grid_color);
			j++;
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:43:36 by frromero          #+#    #+#             */
/*   Updated: 2025/04/10 16:49:53 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void find_player_position(t_game *data, int *x, int *y)
{
	*y = 0;
	while (*y < data->map.height_map)
	{
		*x = 0;
		while (*x < (int)ft_strlen(data->map.map[*y]))
		{
			if (ft_strchr("NSEW", data->map.map[*y][*x]))
			{
				data->player.player_x = (double)*x + 0.5; // Para que Raycasting funcione correctamente
				data->player.player_y = (double)*y + 0.5;
				data->map.map[*y][*x] = '0'; // borramos el caracter del jugador limpiando el mapa
				return;
			}
			(*x)++;
		}
		(*y)++;
	}
}

static int is_valid_position(t_game *data, int x, int y)
{
	if (x < 0 || y < 0 || y >= data->map.height_map ||
		x >= (int)ft_strlen(data->map.map[y]))
		return (0);
	return (1);
}

static int check_map_borders(t_game *data, char **grid, int x, int y)
{
	if (!is_valid_position(data, x, y))
		return (0);
	if (grid[y][x] == ' ' || grid[y][x] == '\0')
		return (0);
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return (1);

	grid[y][x] = 'V';
	if (!check_map_borders(data, grid, x + 1, y) ||
		!check_map_borders(data, grid, x - 1, y) ||
		!check_map_borders(data, grid, x, y + 1) ||
		!check_map_borders(data, grid, x, y - 1))
		return (0);

	return (1);
}

static int check_internal_spaces(t_game *data)
{
	int y;
	int x;

	y = 0;
	while (y < data->map.height_map)
	{
		x = 0;
		while (x < (int)ft_strlen(data->map.map[y]))
		{
			if (data->map.map[y][x] == ' ')
			{
				if (x > 0 && x < (int)ft_strlen(data->map.map[y]) - 1 &&
					y > 0 && y < data->map.height_map - 1)
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

void parse_validate_map(t_game *data)
{
	char **temp_grid;
	int x;
	int y;
	int valid;

	find_player_position(data, &x, &y);
	temp_grid = duplicate_grid(data->map.map, data->map.height_map);
	if (!temp_grid)
	{
		report_err(MALLOC_ERR);
		free_function(data);
		exit(EXIT_FAILURE);
	}
	valid = check_map_borders(data, temp_grid, x, y);
	free_grid(temp_grid, data->map.height_map);
	if (!valid || !check_internal_spaces(data))
	{
		report_err(MAP_PLAYABLE_ERR);
		free_function(data);
		exit(EXIT_FAILURE);
	}
}

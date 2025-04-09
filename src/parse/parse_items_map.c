/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_items_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:08:51 by frromero          #+#    #+#             */
/*   Updated: 2025/04/09 19:42:08 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void add_orientation(t_game *data, int *x, int *y)
{
	data->player.player_x = *x;
	data->player.player_y = *y;
	if (data->map.map[*y][*x] == 'W')
		data->player.player_orinetation = WEST;
	else if (data->map.map[*y][*x] == 'E')
		data->player.player_orinetation = EAST;
	else if (data->map.map[*y][*x] == 'N')
		data->player.player_orinetation = NORTH;
	else if (data->map.map[*y][*x] == 'S')
		data->player.player_orinetation = SOUTH;
}

static void count_and_store_items(t_game *data, int *player)
{
	int x;
	int y;
	int line_len;

	y = 0;
	while (y < data->map.height_map)
	{
		line_len = ft_strlen(data->map.map[y]);
		x = 0;
		while (x < line_len)
		{
			if (data->map.map[y][x] != 'W' && data->map.map[y][x] != 'E' && data->map.map[y][x] != 'S' && data->map.map[y][x] != 'N' && data->map.map[y][x] != '0' && data->map.map[y][x] != '1' && data->map.map[y][x] != ' ' && data->map.map[y][x] != '\t')
			{
				report_err(MAP_ITENS);
				free_function(data);
				exit(EXIT_FAILURE);
			}
			else if (data->map.map[y][x] == 'W' || data->map.map[y][x] == 'E' || data->map.map[y][x] == 'S' || data->map.map[y][x] == 'N')
			{
				add_orientation(data, &x, &y);
				*player = *player + 1;
			}
			x++;
		}
		y++;
	}
}

void parse_items_map(t_game *data)
{
	int player;
	player = 0;

	count_and_store_items(data, &player);
	if (player != 1)
	{
		report_err(MAP_ITENS);
		free_function(data);
		exit(EXIT_FAILURE);
	}
}

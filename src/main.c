/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:17:52 by frromero          #+#    #+#             */
/*   Updated: 2025/04/09 09:20:38 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void init_game(t_game *data)
{
	data->mlx = NULL;
	data->window = NULL;
	data->map.file = NULL;
	data->map.map = NULL;
	data->map.height_map = 0;
	data->map.height_file = 0;
	data->map.sprites.no = NULL;
	data->map.sprites.su = NULL;
	data->map.sprites.we = NULL;
	data->map.sprites.ea = NULL;
	data->player.player_x = -1;
	data->player.player_y = -1;
}

int main(int argc, char **argv)
{
	t_game data;
	int fd;

	if (argc != 2)
		return (report_err(SYNTAX_ERR), 1);
	init_game(&data);
	parse_arg(argv[1], &data);
	print_map_grid(data.map.file, data.map.height_file);
	print_map_grid(data.map.map, data.map.height_map);
	free_function(&data);
	return (0);
}

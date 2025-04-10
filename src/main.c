/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:17:52 by frromero          #+#    #+#             */
/*   Updated: 2025/04/10 23:04:54 by user             ###   ########.fr       */
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
	data->map.paths.north = NULL;
	data->map.paths.south = NULL;
	data->map.paths.east = NULL;
	data->map.paths.west = NULL;
}

int main(int argc, char **argv)
{
	t_game data;
	int fd;

	if (argc != 2)
		return (report_err(SYNTAX_ERR), 1);
	init_game(&data);
	parse_arg(argv[1], &data);
	init_player(&data);
	testing(&data);
	window_init(&data, 800, 600);
	game_loop(&data);
	free_function(&data);
	return (0);
}

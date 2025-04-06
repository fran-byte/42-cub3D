/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:17:52 by frromero          #+#    #+#             */
/*   Updated: 2025/04/06 18:30:13 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void init_game(t_game *data)
{
	data->mlx = NULL;
	data->window = NULL;
	data->map.map_height = 0;
	data->map.raw_map_height = 0;
	data->map.raw_map = NULL;
	data->map.map = NULL;
	data->map.sprites.no = NULL;
	data->map.sprites.su = NULL;
	data->map.sprites.we = NULL;
	data->map.sprites.ea = NULL;
}

int main(int argc, char **argv)
{
	t_game data;
	int fd;

	if (argc != 2)
		return (report_err(SYNTAX_ERR), 1);
	init_game(&data);
	fd = parse_arg(argv[1], &data);
	print_map_grid(data.map.raw_map, data.map.raw_map_height);
	free_function(&data);
	return (0);
}

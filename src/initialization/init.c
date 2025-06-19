/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:10:26 by frromero          #+#    #+#             */
/*   Updated: 2025/05/20 20:45:44 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
 * Initializes all main structures of the game.
 *
 * This file contains functions to set initial default values
 * for player, map, elements, and image data before the game starts.
 */

static void	player_init(t_game *game)
{
	game->player.player_x = -1;
	game->player.player_y = -1;
	game->player.x = 0;
	game->player.y = 0;
	game->player.dir_x = 0;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0;
	game->player.player_orientation = NORTH;
}

static void	elements_init(t_game *game)
{
	game->elem.north = 0;
	game->elem.south = 0;
	game->elem.east = 0;
	game->elem.west = 0;
	game->elem.floor = 0;
	game->elem.ceiling = 0;
}

static void	map_init(t_game *game)
{
	game->map.file = NULL;
	game->map.map = NULL;
	game->map.height_map = 0;
	game->map.height_file = 0;
	game->map.map_start_index = -1;
	game->map.ceiling_color = 0xa3b9a9;
	game->map.floor_color = 0x3b3630;
	game->map.paths.north = NULL;
	game->map.paths.south = NULL;
	game->map.paths.east = NULL;
	game->map.paths.west = NULL;
	game->map.sprites.no = NULL;
	game->map.sprites.su = NULL;
	game->map.sprites.we = NULL;
	game->map.sprites.ea = NULL;
}

static void	image_init(t_game *game)
{
	game->img.img = NULL;
	game->img.addr = NULL;
	game->img.bpp = 0;
	game->img.line_len = 0;
	game->img.endian = 0;
}

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->window = NULL;
	map_init(game);
	player_init(game);
	elements_init(game);
	image_init(game);
}

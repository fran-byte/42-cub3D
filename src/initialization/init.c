/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:10:26 by frromero          #+#    #+#             */
/*   Updated: 2025/05/15 17:25:44 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void player_init(t_game *data)
{
    data->player.player_x = -1;
    data->player.player_y = -1;
    data->player.x = 0;
    data->player.y = 0;
    data->player.dir_x = 0;
    data->player.dir_y = 0;
    data->player.plane_x = 0;
    data->player.plane_y = 0;
    data->player.player_orientation = NORTH;
}

static void elements_init(t_game *data)
{
    data->elem.north = 0;
    data->elem.south = 0;
    data->elem.east = 0;
    data->elem.west = 0;
    data->elem.floor = 0;
    data->elem.ceiling = 0;
}

static void map_init(t_game *data)
{
    data->map.file = NULL;
    data->map.map = NULL;
    data->map.height_map = 0;
    data->map.height_file = 0;
    data->map.map_start_index = -1;
    data->map.celing_color = -1;
    data->map.floor_color = -1;
    data->map.paths.north = NULL;
    data->map.paths.south = NULL;
    data->map.paths.east = NULL;
    data->map.paths.west = NULL;
    data->map.sprites.no = NULL;
    data->map.sprites.su = NULL;
    data->map.sprites.we = NULL;
    data->map.sprites.ea = NULL;
}

static void image_init(t_game *data)
{
    data->img.img = NULL;
    data->img.addr = NULL;
    data->img.bpp = 0;
    data->img.line_len = 0;
    data->img.endian = 0;
}

void init_game(t_game *data)
{
    data->mlx = NULL;
    data->window = NULL;
    map_init(data);
    player_init(data);
    elements_init(data);
    image_init(data);
}
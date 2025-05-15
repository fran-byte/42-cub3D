/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:17:52 by frromero          #+#    #+#             */
/*   Updated: 2025/05/15 14:38:50 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void player(t_game *data)
{
    data->player.player_x = -1;
    data->player.player_y = -1;
    data->player.x = 0;
    data->player.y = 0;
    data->player.dir_x = 0;
    data->player.dir_y = 0;
    data->player.plane_x = 0;
    data->player.plane_y = 0;
    data->player.player_orinetation = NORTH;
}

static void elements(t_game *data)
{
    data->elem.north = 0;
    data->elem.south = 0;
    data->elem.east = 0;
    data->elem.west = 0;
    data->elem.floor = 0;
    data->elem.ceiling = 0;
}

/* Initialize all fields of the t_game structure to safe default values */
static void init_game(t_game *data)
{
    data->mlx = NULL;
    data->window = NULL;
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
    data->img.img = NULL;
    data->img.addr = NULL;
    data->img.bpp = 0;
    data->img.line_len = 0;
    data->img.endian = 0;
    player(data);
    elements(data);
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
    testing(&data); // ****** DEBUG
    window_init(&data, 800, 600);
    game_loop(&data);
    free_function(&data);
    return (0);
}

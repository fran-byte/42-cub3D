/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_items_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:08:51 by frromero          #+#    #+#             */
/*   Updated: 2025/05/15 17:09:53 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void add_orientation(t_game *game, int *x, int *y, int *player)
{
    game->player.player_x = *x;
    game->player.player_y = *y;
    if (game->map.map[*y][*x] == 'W')
        game->player.player_orientation = WEST;
    else if (game->map.map[*y][*x] == 'E')
        game->player.player_orientation = EAST;
    else if (game->map.map[*y][*x] == 'N')
        game->player.player_orientation = NORTH;
    else if (game->map.map[*y][*x] == 'S')
        game->player.player_orientation = SOUTH;
    *player += 1;
}

static void error_items(t_game *data)
{
    report_err(MAP_ITENS_ERR);
    free_function(data);
    exit(EXIT_FAILURE);
}
static void count_and_store_items(t_game *game, int *player)
{
    int x;
    int y;
    int line_len;

    y = 0;
    while (y < game->map.height_map)
    {
        line_len = ft_strlen(game->map.map[y]);
        x = 0;
        while (x < line_len)
        {
            if (game->map.map[y][x] != 'W' && game->map.map[y][x] != 'E' &&
                game->map.map[y][x] != 'S' && game->map.map[y][x] != 'N' &&
                game->map.map[y][x] != '0' && game->map.map[y][x] != '1' &&
                game->map.map[y][x] != ' ' && game->map.map[y][x] != '\t')
                error_items(game);
            else if (game->map.map[y][x] == 'W' || game->map.map[y][x] == 'E' ||
                     game->map.map[y][x] == 'S' || game->map.map[y][x] == 'N')
                add_orientation(game, &x, &y, player);
            x++;
        }
        y++;
    }
}

void parse_items_map(t_game *game)
{
    int player;
    player = 0;

    count_and_store_items(game, &player);
    if (player != 1)
    {
        report_err(MAP_ITENS_ERR);
        free_function(game);
        exit(EXIT_FAILURE);
    }
}

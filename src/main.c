/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:17:52 by frromero          #+#    #+#             */
/*   Updated: 2025/05/20 20:28:32 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Entry point of the Cub3D program.
 *
 * Validates arguments, initializes the game, parses the map file,
 * sets up the player and rendering window, and starts the main loop.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return int Exit status (0 if success, 1 if error).
 */
int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2)
        return (report_err(SYNTAX_ERR), 1);
    init_game(&game);
    parse_arg(argv[1], &game);
    init_player(&game);
    window_init(&game, SCREEN_WIDTH, SCREEN_HEIGHT);
    render_frame(&game);
    game_loop(&game);
    free_function(&game);
    return (0);
}

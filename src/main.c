/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:17:52 by frromero          #+#    #+#             */
/*   Updated: 2025/05/15 18:41:37 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// NO OLVIDAR EN EL MAKEFILE ACTIVAR FLAGS (Están comentadas aún)
// # Warning flags
// #WARN_FLAGS	:= -Wall		# Enable all warnings
// #WARN_FLAGS	+= -Wextra		# Enable extra warnings
// #WARN_FLAGS	+= -Werror		# Treat warnings as errors

int main(int argc, char **argv)
{
    t_game game;
    int fd;

    if (argc != 2)
        return (report_err(SYNTAX_ERR), 1);
    init_game(&game);
    parse_arg(argv[1], &game);
    init_player(&game);
    testing(&game); // ****** DEBUG
    window_init(&game, 800, 600);
    game_loop(&game);
    free_function(&game);
    return (0);
}

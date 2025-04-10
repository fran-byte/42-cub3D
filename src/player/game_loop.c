/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:23:34 by user              #+#    #+#             */
/*   Updated: 2025/04/10 22:31:16 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	exit_game(t_game *game)
{
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	free_function(game);
	exit(0);
	return (0);
}

void	game_loop(t_game *game)
{
    if (!game->mlx || !game->window)
    {
        printf("Error: mlx or window not initialized\n");
        exit(EXIT_FAILURE);
    }
	mlx_hook(game->window, 2, 1L << 0, key_press, game);   // Teclado
	mlx_hook(game->window, 17, 0, exit_game, game);        // Botón cerrar
	mlx_loop(game->mlx);
}
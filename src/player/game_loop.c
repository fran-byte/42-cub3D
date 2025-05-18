/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:23:34 by user              #+#    #+#             */
/*   Updated: 2025/04/11 15:55:13 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int exit_game(t_game *game)
{
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	free_function(game);
	exit(0);
	return (0);
}

void game_loop(t_game *game)
{
	if (!game->mlx || !game->window)
	{
		report_err(MLX_OR_WINDOW_ERR);
		free_function(game);
		exit(EXIT_FAILURE);
	}
	mlx_hook(game->window, 2, 1L << 0, key_press, game); // Teclado
	mlx_hook(game->window, 17, 0, exit_game, game);		 // Botón cerrar
	mlx_loop(game->mlx);
}

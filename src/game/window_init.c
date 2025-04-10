/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:34:10 by user              #+#    #+#             */
/*   Updated: 2025/04/10 22:34:54 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void window_init(t_game *game, int width, int height)
{
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        fprintf(stderr, "Error: mlx_init failed\n");
        exit(EXIT_FAILURE);
    }

    game->window = mlx_new_window(game->mlx, width, height, "Cub3D");
    if (!game->window)
    {
        fprintf(stderr, "Error: mlx_new_window failed\n");
        exit(EXIT_FAILURE);
    }

    // Inicializa otros elementos de la estructura `game` si es necesario
}
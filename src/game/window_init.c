/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:34:10 by user              #+#    #+#             */
/*   Updated: 2025/05/15 17:51:20 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void window_init(t_game *game, int width, int height)
{
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        report_err(MLX_INIT_ERR);
        free_function(game);
        exit(EXIT_FAILURE);
    }

    game->window = mlx_new_window(game->mlx, width, height, "Cub3D");
    if (!game->window)
    {
        mlx_destroy_display(game->mlx);
        report_err(MLX_NEW_WINDOW_ERR);
        free_function(game);
        exit(EXIT_FAILURE);
    }

    game->img.img = mlx_new_image(game->mlx, width,
                                  height); // AÑADIDA
    game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, // AÑADIDA
                                       &game->img.line_len, &game->img.endian);
    load_textures(game); // AÑADIDA *********************
}

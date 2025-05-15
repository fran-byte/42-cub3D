/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:32:33 by frromero          #+#    #+#             */
/*   Updated: 2025/05/15 19:10:50 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Frees memory allocated for texture file paths.
 *
 * @param data Pointer to the game data structure.
 */
static void free_texture_paths(t_game *data)
{

    if (data->map.paths.north)
    {
        free(data->map.paths.north);
        data->map.paths.north = NULL;
    }
    if (data->map.paths.south)
    {
        free(data->map.paths.south);
        data->map.paths.south = NULL;
    }
    if (data->map.paths.west)
    {
        free(data->map.paths.west);
        data->map.paths.west = NULL;
    }
    if (data->map.paths.east)
    {
        free(data->map.paths.east);
        data->map.paths.east = NULL;
    }
}

/**
 * @brief Frees a matrix (2D array) of characters.
 *
 * @param matrix The matrix to free.
 * @param height Number of rows in the matrix.
 */
void free_char_matrix(char **matrix, int height)
{
    if (matrix != NULL)
    {
        int i;

        i = 0;
        while (i < height)
        {
            if (matrix[i] != NULL)
                free(matrix[i]);
            i++;
        }
        free(matrix);
    }
}

/**
 * @brief Frees the resources inside the map structure.
 *
 * @param map Pointer to the map structure to free.
 */
void free_map(t_map *map)
{
    if (map != NULL)
    {
        if (map->file != NULL && map->height_file > 0)
        {
            free_char_matrix(map->file, map->height_file);
        }
        if (map->map != NULL && map->height_map > 0)
        {
            free_char_matrix(map->map, map->height_map);
        }

        /* Si t_sprites necesitan liberación, hacerlo aquí*/
    }
}

/**
 * @brief Frees the main game structure and its components.
 *
 * @param data Pointer to the game data structure to free.
 */
void free_function(t_game *data)
{
    if (data != NULL)
    {
        free_map(&data->map);
        free_texture_paths(data);

        /*Liberar otros miembros de t_game (como mlx, window, etc.)
         if (game->mlx != NULL)
         {
                 mlx_destroy_window(game->mlx, game->window);
         }
         free(game);*/
    }
}

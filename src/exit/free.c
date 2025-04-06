/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:32:33 by frromero          #+#    #+#             */
/*   Updated: 2025/04/06 21:51:24 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Función para liberar las matrices de caracteres usando while
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

// Función para liberar la estructura t_map
void free_map(t_map *map)
{
	if (map != NULL)
	{
		if (map->map_file != NULL && map->height_file > 0)
		{
			free_char_matrix(map->map_file, map->height_file);
		}
		if (map->map != NULL && map->height_map > 0)
		{
			free_char_matrix(map->map, map->height_map);
		}

		// Si `t_sprites` necesitan liberación, hacerlo aquí
	}
}

// Liberando estructura t_game
void free_function(t_game *game)
{
	if (game != NULL)
	{
		free_map(&game->map);

		// Liberar otros miembros de t_game (como mlx, window, etc.)
		// if (game->mlx != NULL)
		// {
		// 	mlx_destroy_window(game->mlx, game->window);
		// }
		// free(game);
	}
}

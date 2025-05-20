/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_load_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:47:40 by frromero          #+#    #+#             */
/*   Updated: 2025/05/15 19:14:18 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Verifies that all texture sizes match.
 *
 * This function compares the width and height of all loaded textures to ensure
 * they are consistent. Only the first four textures are considered (indexed 0
 * to 3).
 *
 * @param w Array of texture widths.
 * @param h Array of texture heights.
 * @return true if all textures have the same width and height as the first one,
 * false otherwise.
 */
bool	check_texture_sizes(int *w, int *h)
{
	for (int i = 1; i < 4; i++)
	{
		if (w[i] != w[0] || h[i] != h[0])
			return (false);
	}
	return (true);
}

/**
 * @brief Cleans up allocated resources and exits the program.
 *
 * This function destroys loaded textures and frees all allocated memory
 * before exiting the program with the given exit code.
 *
 * @param g Pointer to the main game structure.
 * @param exit_code Exit status code to return to the operating system.
 */
void	clean_exit(t_game *g, int exit_code)
{
	if (g->map.sprites.no)
		mlx_destroy_image(g->mlx, g->map.sprites.no);
	if (g->map.sprites.su)
		mlx_destroy_image(g->mlx, g->map.sprites.su);
	if (g->map.sprites.ea)
		mlx_destroy_image(g->mlx, g->map.sprites.ea);
	if (g->map.sprites.we)
		mlx_destroy_image(g->mlx, g->map.sprites.we);
	free_function(g);
	exit(exit_code);
}
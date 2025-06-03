/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_store_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:29:10 by frromero          #+#    #+#             */
/*   Updated: 2025/06/03 07:33:33 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Extracts and stores a texture path from a line.
 *
 * Trims whitespace from the path in the provided line, checks if the file
 * is accessible, and stores it in the destination pointer.
 * Exits on memory allocation or access error.
 *
 * @param game Pointer to the game data structure.
 * @param line The line containing the texture directive and path.
 * @param dest Pointer to where the extracted path will be stored.
 */
void	store_path(t_game *game, char *line, char **dest)
{
	char	*path;

	path = ft_strtrim(line + 2, " \t");
	if (!path)
	{
		report_err(MALLOC_ERR);
		free_function(game);
		exit(EXIT_FAILURE);
	}
    path = ft_strtrim(path, " ");
	if (access(path, R_OK) != 0)
	{
		free(path);
		report_err(TEXTURE_FILE_ERR);
		free_function(game);
		exit(EXIT_FAILURE);
	}
	*dest = path;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:19:35 by frromero          #+#    #+#             */
/*   Updated: 2025/06/11 14:13:18 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Copies the map lines from the original file.
 *
 * Allocates and duplicates each map line starting from the specified index.
 * Frees memory and returns NULL on allocation failure.
 *
 * @param game Pointer to the game data structure.
 * @param start_index Index where the map starts in the file array.
 * @return char** A new array of strings containing the map lines.
 */
static char	**extract_map_lines(t_game *game, int start_index)
{
	char	**map;
	int		i;

	i = 0;
	map = (char **)malloc(sizeof(char *) * (game->map.height_map + 1));
	if (!map)
		return (NULL);
	while (i < game->map.height_map)
	{
		map[i] = ft_strdup(game->map.file[start_index + i]);
		if (!map[i])
		{
			free_split(map);
			return (NULL);
		}
		i++;
	}
	map[i] = NULL;

	return (map);
}

int parse_size(t_game *game)
{
    int i;

    i = 0;
    if (game->map.height_map > MAX_SIZE)
        return (0);
    while (i < game->map.height_map) {
        if (ft_strlen(game->map.map[i]) > MAX_SIZE)
            return (0);
        i++;
    }
    return (1);
}

/**
 * @brief Parses the map from the .cub file.
 *
 * Sets the map height, allocates and copies the map lines.
 * Then checks for player/items and validates the map format.
 * Exits on errors such as empty map or allocation failure.
 *
 * @param game Pointer to the game data structure.
 */
void	parse_map(t_game *game)
{
	int	i;
	int	height;

	height = 0;
	i = game->map.map_start_index;
	while (game->map.file[i + height])
		height++;
	game->map.height_map = height;
	if (game->map.height_map == 0)
	{
		report_err(MAP_VOID_ERR);
		free_function(game);
		exit(EXIT_FAILURE);
	}
	game->map.map = extract_map_lines(game, i);
	if (!game->map.map)
	{
		report_err(MAP_VOID_ERR);
		free_function(game);
		exit(EXIT_FAILURE);
	}
    if (!parse_size(game))
	{
		report_err(MAP_MAX_ERR);
		free_function(game);
		exit(EXIT_FAILURE);
	}
	parse_items_map(game);
	parse_validate_map(game);
}

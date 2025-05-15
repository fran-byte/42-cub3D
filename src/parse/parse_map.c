/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:19:35 by frromero          #+#    #+#             */
/*   Updated: 2025/05/15 18:52:45 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Calculates the height of the map.
 *
 * Counts the number of lines starting from the 9th line (index 8) in the file.
 * Returns 0 if the map data is missing or incomplete.
 *
 * @param data Pointer to the game data structure.
 * @return int Height of the map (number of lines).
 */
static int calculate_map_height(t_game *data)
{
    int height;
    char **lines;

    height = 0;
    if (!data->map.file || !data->map.file[8])
        return (0);
    lines = data->map.file + 8;
    while (lines != NULL && *lines != NULL)
    {
        lines++;
        height++;
    }
    return (height);
}

/**
 * @brief Copies the map lines from the original file.
 *
 * Allocates and duplicates each map line starting from the specified index.
 * Frees memory and returns NULL on allocation failure.
 *
 * @param data Pointer to the game data structure.
 * @param start_index Index where the map starts in the file array.
 * @return char** A new array of strings containing the map lines.
 */
static char **extract_map_lines(t_game *data, int start_index)
{
    char **map;
    int i;

    i = 0;
    map = (char **)malloc(sizeof(char *) * (data->map.height_map + 1));
    if (!map)
        return (NULL);

    while (i < data->map.height_map)
    {
        map[i] = ft_strdup(data->map.file[start_index + i]);
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

/**
 * @brief Parses the map from the .cub file.
 *
 * Sets the map height, allocates and copies the map lines.
 * Then checks for player/items and validates the map format.
 * Exits on errors such as empty map or allocation failure.
 *
 * @param data Pointer to the game data structure.
 */
void parse_map(t_game *data)
{
    int i;
    int height;

    height = 0;
    i = data->map.map_start_index;
    while (data->map.file[i + height])
        height++;
    data->map.height_map = height;
    if (data->map.height_map == 0)
    {
        report_err(MAP_VOID_ERR);
        free_function(data);
        exit(EXIT_FAILURE);
    }
    data->map.map = extract_map_lines(data, i);
    if (!data->map.map)
    {
        report_err(MAP_VOID_ERR);
        free_function(data);
        exit(EXIT_FAILURE);
    }
    parse_items_map(data);
    parse_validate_map(data);
}

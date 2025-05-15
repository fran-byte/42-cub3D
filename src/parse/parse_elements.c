/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:50:04 by frromero          #+#    #+#             */
/*   Updated: 2025/05/15 18:49:52 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Processes texture identifiers (NO, SO, WE, EA) and stores their paths.
 *
 * Each valid texture is stored only once and increases the parsed element
 * count.
 *
 * @param data Pointer to the main game structure.
 * @param elem Pointer to the counter of parsed elements.
 * @param i Pointer to the current line index in the map file.
 */
static void process_textures(t_game *data, int *elem, int *i)
{
    if (ft_strncmp(data->map.file[*i], "NO ", 3) == 0 && !data->elem.north)
    {
        store_path(data, data->map.file[*i], &data->map.paths.north);
        data->elem.north = 1;
        *elem += 1;
    }
    else if (ft_strncmp(data->map.file[*i], "SO ", 3) == 0 && !data->elem.south)
    {
        store_path(data, data->map.file[*i], &data->map.paths.south);
        data->elem.south = 1;
        *elem += 1;
    }
    else if (ft_strncmp(data->map.file[*i], "WE ", 3) == 0 && !data->elem.west)
    {
        store_path(data, data->map.file[*i], &data->map.paths.west);
        data->elem.west = 1;
        *elem += 1;
    }
    else if (ft_strncmp(data->map.file[*i], "EA ", 3) == 0 && !data->elem.east)
    {
        store_path(data, data->map.file[*i], &data->map.paths.east);
        data->elem.east = 1;
        *elem += 1;
    }
}

/**
 * @brief Parses floor and ceiling color definitions (F and C).
 *
 * Converts RGB strings to integers and stores them.
 *
 * @param data Pointer to the game structure.
 * @param elem Pointer to the element counter.
 * @param i Pointer to the current index in the file.
 */
static void process_colors(t_game *data, int *elem, int *i)
{
    if (ft_strncmp(data->map.file[*i], "F ", 2) == 0 && !data->elem.floor)
    {
        parse_color_line(data, data->map.file[*i]);
        data->elem.floor = 1;
        *elem += 1;
    }
    else if (ft_strncmp(data->map.file[*i], "C ", 2) == 0 &&
             !data->elem.ceiling)
    {
        parse_color_line(data, data->map.file[*i]);
        data->elem.ceiling = 1;
        *elem += 1;
    }
}

/**
 * @brief Validates element count and determines the start of the map.
 *
 * Ensures all required elements are present and skips empty lines before the
 * map.
 *
 * @param data Pointer to the game structure.
 * @param elem Pointer to the element counter.
 * @param i Pointer to the current index in the file.
 */
static void elements_and_file(t_game *data, int *elem, int *i)
{
    if (*elem != 6)
    {
        report_err(MISSING_ELEMENT_ERR);
        free_function(data);
        exit(EXIT_FAILURE);
    }
    while (data->map.file[*i] && is_empty_line(data->map.file[*i]))
        *i += 1;
    if (!data->map.file[*i])
    {
        report_err(MAP_VOID_ERR);
        free_function(data);
        exit(EXIT_FAILURE);
    }
    data->map.map_start_index = *i;
}

/**
 * @brief Handles format errors in element parsing.
 *
 * Cleans up memory and exits the program.
 *
 * @param data Pointer to the game structure.
 */
static void parse_error(t_game *data)
{
    report_err(ELEMENT_FORMAT_ERR);
    free_function(data);
    exit(EXIT_FAILURE);
}

/**
 * @brief Main parser for configuration elements in the .cub file.
 *
 * Iterates through the file, identifying texture and color lines.
 * Handles validation and structure updates accordingly.
 *
 * @param data Pointer to the main game structure.
 */
void parse_elements(t_game *data)
{
    int i;
    int elem;

    i = 0;
    elem = 0;
    data->elem = (t_elem){0};
    while (data->map.file[i] && elem < 6)
    {
        if (is_empty_line(data->map.file[i]))
        {
            i++;
            continue;
        }
        process_textures(data, &elem, &i);
        process_colors(data, &elem, &i);
        if (elem == 0 ||
            (!data->elem.north && !data->elem.south && !data->elem.west &&
             !data->elem.east && !data->elem.floor && !data->elem.ceiling))
            parse_error(data);
        i++;
    }
    elements_and_file(data, &elem, &i);
}

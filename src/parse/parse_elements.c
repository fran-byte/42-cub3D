/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:50:04 by frromero          #+#    #+#             */
/*   Updated: 2025/06/07 16:27:38 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Processes texture identifiers (NO, SO, WE, EA) and stores their paths.
 *
 * Each valid texture is stored only once and increases the parsed element
 * count.
 *
 * @param game Pointer to the main game structure.
 * @param elem Pointer to the counter of parsed elements.
 * @param i Pointer to the current line index in the map file.
 */
static void	process_textures(t_game *game, int *elem, int *i)
{
	if (ft_strncmp(game->map.file[*i], "NO ", 3) == 0 && !game->elem.north)
	{
		store_path(game, game->map.file[*i], &game->map.paths.north);
		game->elem.north = 1;
		*elem += 1;
	}
	else if (ft_strncmp(game->map.file[*i], "SO ", 3) == 0 && !game->elem.south)
	{
		store_path(game, game->map.file[*i], &game->map.paths.south);
		game->elem.south = 1;
		*elem += 1;
	}
	else if (ft_strncmp(game->map.file[*i], "WE ", 3) == 0 && !game->elem.west)
	{
		store_path(game, game->map.file[*i], &game->map.paths.west);
		game->elem.west = 1;
		*elem += 1;
	}
	else if (ft_strncmp(game->map.file[*i], "EA ", 3) == 0 && !game->elem.east)
	{
		store_path(game, game->map.file[*i], &game->map.paths.east);
		game->elem.east = 1;
		*elem += 1;
	}
}

/**
 * @brief Parses floor and ceiling color definitions (F and C).
 *
 * Converts RGB strings to integers and stores them.
 *
 * @param game Pointer to the game structure.
 * @param elem Pointer to the element counter.
 * @param i Pointer to the current index in the file.
 */
static void	process_colors(t_game *game, int *elem, int *i)
{
	if (ft_strncmp(game->map.file[*i], "F ", 2) == 0 && !game->elem.floor)
	{
		game->map.floor_color = parse_color_line(game, game->map.file[*i]);
		game->elem.floor = 1;
		*elem += 1;
	}
	else if (ft_strncmp(game->map.file[*i], "C ", 2) == 0
		&& !game->elem.ceiling)
	{
		game->map.ceiling_color = parse_color_line(game, game->map.file[*i]);
		game->elem.ceiling = 1;
		*elem += 1;
	}
}

/**
 * @brief Validates element count and determines the start of the map.
 *
 * Ensures all required elements are present and skips empty lines before the
 * map.
 *
 * @param game Pointer to the game structure.
 * @param elem Pointer to the element counter.
 * @param i Pointer to the current index in the file.
 */
static void	elements_and_file(t_game *game, int *elem, int *i)
{
	if (*elem != 6)
	{
		report_err(MISSING_ELEMENT_ERR);
		free_function(game);
		exit(EXIT_FAILURE);
	}
	while (game->map.file[*i] && is_empty_line(game->map.file[*i]))
		*i += 1;
	if (!game->map.file[*i])
	{
		report_err(MAP_VOID_ERR);
		free_function(game);
		exit(EXIT_FAILURE);
	}
	game->map.map_start_index = *i;
}

/**
 * @brief Handles format errors in element parsing.
 *
 * Cleans up memory and exits the program.
 *
 * @param game Pointer to the game structure.
 */
static void	parse_error(t_game *game)
{
	report_err(ELEMENT_FORMAT_ERR);
	free_function(game);
	exit(EXIT_FAILURE);
}

/**
 * @brief Main parser for configuration elements in the .cub file.
 *
 * Iterates through the file, identifying textures and color lines.
 * Handles validation and structure updates accordingly.
 * (6 elemnts: NO SO WE EA C F)
 *
 * @param game Pointer to the main game structure.
 */
void	parse_elements(t_game *game)
{
	int	i;
	int	elem;    

	i = 0;
	elem = 0;
	game->elem = (t_elem){0};
	while (game->map.file[i] && elem < 6)
	{
		if (is_empty_line(game->map.file[i]))
		{
			i++;
			continue ;
		}
        ft_strstrimed(game, i); 
		process_textures(game, &elem, &i);
		process_colors(game, &elem, &i);
		if (elem == 0 || (!game->elem.north && !game->elem.south
				&& !game->elem.west && !game->elem.east && !game->elem.floor
				&& !game->elem.ceiling))
			parse_error(game);
		i++;
	}
	elements_and_file(game, &elem, &i);
}

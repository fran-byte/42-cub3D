#include "../../include/cub3d.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:37:27 by frromero          #+#    #+#             */
/*   Updated: 2025/04/08 17:25:03 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Frees memory and exits on color format error.
 */
static void exit_error_color(t_game *game, char **grid)
{
    if (grid)
        free_split(grid);
    report_err(FORMAT_COLOR_ERR);
    free_function(game);
    exit(EXIT_FAILURE);
}

/**
 * @brief Returns 1 if the string is numeric, 0 otherwise.
 */
static int is_numeric(const char *str)
{
    while (*str)
    {
        if (!ft_isdigit(*str))
            return (0);
        str++;
    }
    return (1);
}

/**
 * @brief Parses an RGB color line from the map file.
 *
 * Validates and extracts RGB values from a string (e.g., "F 220,100,0").
 * Ensures values are numeric and within the 0–255 range. Exits on error.
 *
 * @param game Pointer to the main game structure.
 * @param line The line containing the color definition.
 */
void parse_color_line(t_game *game, char *line)
{
    char **rgb;
    int r;
    int g;
    int b;

    r = 0;
    g = 0;
    b = 0;
    rgb = ft_split(line + 2, ',');
    if (!rgb || ft_array_size(rgb) != 3)
        exit_error_color(game, rgb);
    if (!is_numeric(rgb[0]) || !is_numeric(rgb[1]) || !is_numeric(rgb[2]))
        exit_error_color(game, rgb);
    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        exit_error_color(game, rgb);
    free_split(rgb);
}

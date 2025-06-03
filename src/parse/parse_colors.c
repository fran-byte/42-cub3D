/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:50:04 by frromero          #+#    #+#             */
/*   Updated: 2025/06/03 10:50:06 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Frees up to three pointers and optionally exits the program.
 *
 * @param game Main game structure (for exiting).
 * @param ptrs Array of pointers to free (up to 3 elements, can contain NULL).
 * @param split Array of strings to free (can be NULL).
 * @param exit_flag If 1, the function will terminate the program.
 */
static void free_and_exit(t_game *game, void *ptrs[3], char **split, int exit_flag)
{
    int i;
    
    i = 0;
    while (i < 3)
    {
        if (ptrs[i])
            free(ptrs[i]);
        i++;
    }
    if (split)
        free_split(split);
    if (exit_flag)
    {
        report_err(FORMAT_COLOR_ERR);
        free_function(game);
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Returns 1 if the string is numeric, 0 otherwise.
 */
static int is_numeric(const char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

/**
 * @brief Cleans spaces and validates if a string is numeric.
 * 
 * @param color The color string to process.
 * @return Cleaned string or NULL if invalid.
 */
static char *clean_and_validate_color(char *color)
{
    char *cleaned;
    
    cleaned = ft_strtrim(color, " ");
    if (!cleaned || !is_numeric(cleaned))
    {
        free(cleaned);
        return (NULL);
    }
    return (cleaned);
}

/**
 * @brief Parses an RGB color line from the map file.
 *
 * Validates and extracts RGB values from a string (e.g., "F 220,100,0").
 * Ensures values are numeric and within the 0–255 range.
 * Exits with an error if values are invalid.
 *
 * @param game Pointer to the main game structure.
 * @param line The line containing the color definition.
 */
int parse_color_line(t_game *game, char *line)
{
    char **rgb;
    char *clean[3];
    int r, g, b;
    void *ptrs[3];

    rgb = ft_split(line + 2, ',');
    if (!rgb || ft_array_size(rgb) != 3)
        free_and_exit(game, NULL, rgb, 1);    
    clean[0] = clean_and_validate_color(rgb[0]);
    clean[1] = clean_and_validate_color(rgb[1]);
    clean[2] = clean_and_validate_color(rgb[2]);
    ptrs[0] = clean[0];
    ptrs[1] = clean[1];
    ptrs[2] = clean[2];
    if (!clean[0] || !clean[1] || !clean[2])
        free_and_exit(game, ptrs, rgb, 1);
    r = ft_atoi(clean[0]);
    g = ft_atoi(clean[1]);
    b = ft_atoi(clean[2]);
    free_and_exit(game, ptrs, rgb, 0);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        free_and_exit(game, NULL, NULL, 1);
    return ((r << 16) | (g << 8) | b);
}

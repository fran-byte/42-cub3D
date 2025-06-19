/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:50:04 by frromero          #+#    #+#             */
/*   Updated: 2025/06/07 14:28:15 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Checks if the input string contains only digits.
 *
 * @param str The string to check.
 * @return 1 if the string is numeric, 0 otherwise.
 */
static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '+')
			return (1);
		else if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Trims and validates a single RGB color component string.
 *
 * Removes leading/trailing spaces and checks if the result is a numeric value.
 *
 * @param color The raw RGB component string.
 * @return A newly allocated trimmed string if valid, NULL otherwise.
 */
static char	*clean_and_validate_color(char *color)
{
	char	*trimmed;
	int		valid;

	trimmed = ft_strtrim(color, " ");
	if (!trimmed)
		return (NULL);
	valid = is_numeric(trimmed);
	if (!valid)
	{
		free(trimmed);
		return (NULL);
	}
	return (trimmed);
}

/**
 * @brief Frees resources used during color parsing and optionally exits.
 *
 * Frees dynamically allocated color strings and the RGB split array.
 * If exit_flag is set, an error message is reported and the program exits.
 *
 * @param game Pointer to the game structure.
 * @param ptrs Array of allocated strings to free.
 * @param split The split RGB components array to free.
 * @param exit_flag If set to 1, triggers an exit with error reporting.
 */
static void	free_color_resources(t_game *game, void *ptrs[3], char **split,
		int exit_flag)
{
	int	i;

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
 * @brief Extracts and converts RGB values from strings to an integer color.
 *
 * Validates and trims each color component, checks the 0-255 range,
 * and combines the values into a single RGB integer.
 *
 * @param game Pointer to the game structure.
 * @param rgb The array of RGB component strings.
 * @return The packed RGB value as an integer.
 */
static int	extract_rgb_values(t_game *game, char **rgb)
{
	void	*ptrs[3];
	char	*clean[3];
	int		r;
	int		g;
	int		b;

	clean[0] = clean_and_validate_color(rgb[0]);
	clean[1] = clean_and_validate_color(rgb[1]);
	clean[2] = clean_and_validate_color(rgb[2]);
	ptrs[0] = clean[0];
	ptrs[1] = clean[1];
	ptrs[2] = clean[2];
	if (!clean[0] || !clean[1] || !clean[2])
		free_color_resources(game, ptrs, rgb, 1);
	r = ft_atoi(clean[0]);
	g = ft_atoi(clean[1]);
	b = ft_atoi(clean[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		free_color_resources(game, ptrs, rgb, 1);
	free_color_resources(game, ptrs, rgb, 0);
	return ((r << 16) | (g << 8) | b);
}

/**
 * @brief Parses a line containing a color definition for floor or ceiling.
 *
 * Splits the line by commas, validates each color component, and returns
 * the combined RGB integer. Exits on invalid input.
 *
 * @param game Pointer to the game structure.
 * @param line The input line from the map file (e.g. "F 220,100,0").
 * @return The packed RGB value as an integer.
 */
int	parse_color_line(t_game *game, char *line)
{
	char	**rgb;
	int		result;

	rgb = ft_split(line + 2, ',');
	if (!rgb)
		free_color_resources(game, NULL, rgb, 1);
	if (ft_array_size(rgb) != 3)
	{
		free_split(rgb);
		report_err("Invalid color format: expected R,G,B");
		free_function(game);
		exit(EXIT_FAILURE);
	}
	result = extract_rgb_values(game, rgb);
	return (result);
}

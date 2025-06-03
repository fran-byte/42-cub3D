/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:50:04 by frromero          #+#    #+#             */
/*   Updated: 2025/06/03 16:17:49 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

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
	free_color_resources(game, ptrs, rgb, 0);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		free_color_resources(game, NULL, NULL, 1);
	return ((r << 16) | (g << 8) | b);
}

int	parse_color_line(t_game *game, char *line)
{
	char	**rgb;
	int		result;

	rgb = ft_split(line + 2, ',');
	if (!rgb || ft_array_size(rgb) != 3)
		free_color_resources(game, NULL, rgb, 1);
	result = extract_rgb_values(game, rgb);
	return (result);
}

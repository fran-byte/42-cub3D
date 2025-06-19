/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:43:36 by frromero          #+#    #+#             */
/*   Updated: 2025/05/20 20:09:22 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Finds the initial player position in the map.
 *
 * Replaces the position in the map with '0' once located.
 *
 * @param game Pointer to the game structure.
 * @param x Pointer to store the player's x-coordinate.
 * @param y Pointer to store the player's y-coordinate.
 */
static void	find_player_position(t_game *game, int *x, int *y)
{
	*y = 0;
	while (*y < game->map.height_map)
	{
		*x = 0;
		while (*x < (int)ft_strlen(game->map.map[*y]))
		{
			if (ft_strchr("NSEW", game->map.map[*y][*x]))
			{
				game->player.player_x = (double)*x + 0.5;
				game->player.player_y = (double)*y + 0.5;
				game->map.map[*y][*x] = '0';
				return ;
			}
			(*x)++;
		}
		(*y)++;
	}
}

/**
 * @brief Checks if a coordinate is within the map bounds.
 *
 * @param game Pointer to the game structure.
 * @param x X-coordinate to validate.
 * @param y Y-coordinate to validate.
 * @return 1 if valid, 0 if out of bounds.
 */
static int	is_valid_position(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || y >= game->map.height_map
		|| x >= (int)ft_strlen(game->map.map[y]))
		return (0);
	return (1);
}

/**
 * @brief Checks if a map character is walkable.
 *
 * @param c Character from the map grid.
 * @return 1 if character is traversable, 0 otherwise.
 */
static int	is_traversable(char c)
{
	return (c == '0' || c == ' ' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}

/**
 * @brief Recursively checks that the map is properly enclosed.
 *
 * Performs a flood fill from the player's position to ensure no leaks.
 *
 * @param game Pointer to the game structure.
 * @param grid Copy of the map to validate.
 * @param x Current x-coordinate being checked.
 * @param y Current y-coordinate being checked.
 * @return 1 if map is valid, 0 if invalid or open.
 */
static int	check_map_borders(t_game *game, char **grid, int x, int y)
{
	if (!is_valid_position(game, x, y))
		return (0);
	if (grid[y][x] == '\0')
		return (0);
	if (grid[y][x] == '1' || grid[y][x] == '\t' || grid[y][x] == 'V')
		return (1);
	if (!is_traversable(grid[y][x]))
		return (0);
	grid[y][x] = 'V';
	if (!check_map_borders(game, grid, x + 1, y) || !check_map_borders(game,
			grid, x - 1, y) || !check_map_borders(game, grid, x, y + 1)
		|| !check_map_borders(game, grid, x, y - 1))
		return (0);
	return (1);
}

/**
 * @brief Validates the overall structure of the map.
 *
 * Ensures the map is closed and the player's position is valid.
 * Exits if validation fails.
 *
 * @param game Pointer to the game structure.
 */
void	parse_validate_map(t_game *game)
{
	char	**temp_grid;
	int		x;
	int		y;
	int		valid;

	x = 0;
	find_player_position(game, &x, &y);
	temp_grid = duplicate_grid(game->map.map, game->map.height_map);
	if (!temp_grid)
	{
		report_err(MALLOC_ERR);
		free_function(game);
		exit(EXIT_FAILURE);
	}
	valid = check_map_borders(game, temp_grid, x, y);
	free_grid(temp_grid, game->map.height_map);
	if (!valid)
	{
		report_err(MAP_PLAYABLE_ERR);
		free_function(game);
		exit(EXIT_FAILURE);
	}
}

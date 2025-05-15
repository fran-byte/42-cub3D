/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:16:50 by frromero          #+#    #+#             */
/*   Updated: 2025/05/15 19:06:56 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Frees a dynamically allocated 2D grid of strings.
 *
 * @param grid The 2D array (grid) to free.
 * @param height Number of rows in the grid.
 */
void free_grid(char **grid, int height)
{
    int i;

    i = 0;
    while (i < height)
    {
        free(grid[i]);
        i++;
    }
    free(grid);
}

/**
 * @brief Duplicates a 2D grid of strings.
 *
 * @param grid The original 2D array (grid) to copy.
 * @param height Number of rows in the grid.
 * @return A newly allocated duplicated grid, or NULL if allocation fails.
 */
char **duplicate_grid(char **grid, int height)
{
    char **new_grid;
    int i;

    i = 0;
    new_grid = malloc(sizeof(char *) * height);
    if (!new_grid)
        return (NULL);
    while (i < height)
    {
        new_grid[i] = ft_strdup(grid[i]);
        if (!new_grid[i])
        {
            while (i > 0)
                free(new_grid[--i]);
            free(new_grid);
            return (NULL);
        }
        i++;
    }
    return (new_grid);
}

/**
 * @brief Checks if a character is a whitespace character.
 *
 * @param c The character to check.
 * @return Non-zero if c is whitespace, zero otherwise.
 */
int ft_isspace(int c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' ||
            c == '\r');
}

/**
 * @brief Determines if a line is empty or contains only whitespace.
 *
 * @param line The string line to check.
 * @return 1 if the line is empty or NULL, 0 otherwise.
 */
int is_empty_line(char *line)
{
    if (!line)
        return (1);

    while (*line)
    {
        if (!ft_isspace(*line))
            return (0);
        line++;
    }
    return (1);
}

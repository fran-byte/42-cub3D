/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:32:50 by frromero          #+#    #+#             */
/*   Updated: 2025/05/15 19:28:18 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Opens a file for reading.
 *
 * Exits the program if the file cannot be opened.
 *
 * @param arg The path to the file.
 * @param game Pointer to the game data structure for cleanup on error.
 * @return File descriptor of the opened file.
 */
int open_file(char *arg, t_game *game)
{
    int fd;

    fd = open(arg, O_RDONLY);
    if (fd < 0)
    {
        report_err(OPEN_FILE_ERR);
        free_function(game);
        exit(EXIT_FAILURE);
    }
    return (fd);
}

/**
 * @brief Frees a NULL-terminated array of strings.
 *
 * @param grid_color The array of strings to free.
 */
void free_split(char **grid_color)
{
    int i;

    if (!grid_color)
        return;
    i = 0;
    while (grid_color[i])
    {
        free(grid_color[i]);
        i++;
    }
    free(grid_color);
}

/**
 * @brief Checks if a string contains only numeric characters.
 *
 * @param str The string to check.
 * @return 1 if the string is numeric, 0 otherwise.
 */
int is_numeric(const char *str)
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
 * @brief Counts occurrences of a character in a string.
 *
 * @param str The string to search.
 * @param c The character to count.
 * @return Number of times c appears in str.
 */
int count_char_in_str(const char *str, char c)
{
    int count;
    int i;

    count = 0;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == c)
            count++;
        i++;
    }
    return (count);
}

/**
 * @brief Returns the size of a NULL-terminated array of strings.
 *
 * @param array The array to measure.
 * @return Number of strings in the array.
 */
int ft_array_size(char **array)
{
    int count;

    count = 0;
    while (array && array[count])
        count++;
    return (count);
}

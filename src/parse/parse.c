/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 23:43:36 by frromero          #+#    #+#             */
/*   Updated: 2025/05/15 19:26:26 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Exits the program with a memory allocation error.
 *
 * This function is called when memory allocation fails during
 * the file grid filling process. It prints an error, closes the file,
 * frees all game resources, and exits.
 *
 * @param fd File descriptor of the opened file.
 * @param game Pointer to the main game structure.
 */
static void util_exit_fill_file_grid(int fd, t_game *game)
{
    report_err(MALLOC_ERR);
    close(fd);
    free_function(game);
    exit(EXIT_FAILURE);
}

/**
 * @brief Fills the file grid with lines read from the .cub file.
 *
 * Reads each line from the specified file and stores it in
 * the `game->map.file` array for later parsing.
 *
 * @param arg Path to the .cub file.
 * @param game Pointer to the main game structure.
 */
static void fill_file_grid(char *arg, t_game *game)
{
    char *line;
    int i;
    int fd;
    int len;

    fd = open_file(arg, game);
    i = 0;
    line = get_next_line(fd);

    while (line != NULL && i < game->map.height_file)
    {
        len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';

        game->map.file[i] = malloc(len + 1);
        if (!game->map.file[i])
            util_exit_fill_file_grid(fd, game);

        ft_strlcpy(game->map.file[i], line, len + 1);
        free(line);
        line = get_next_line(fd);
        i++;
    }

    game->map.file[i] = NULL;
    close(fd);
}

/**
 * @brief Calculates the number of lines in the .cub file.
 *
 * Iterates through the file to count how many lines it contains
 * and stores the result in `game->map.height_file`.
 *
 * @param fd File descriptor of the opened file.
 * @param game Pointer to the main game structure.
 */
void get_height_map(int fd, t_game *game)
{
    char *line;

    game->map.height_file = 0;
    line = get_next_line(fd);

    while (line != NULL)
    {
        game->map.height_file++;
        free(line);
        line = get_next_line(fd);
    }

    close(fd);
}

/**
 * @brief Loads the content of the .cub file into memory.
 *
 * Allocates memory for `game->map.file`, calculates the height,
 * and fills the grid with the file's contents.
 *
 * @param arg Path to the .cub file.
 * @param game Pointer to the main game structure.
 */
void load_file(char *arg, t_game *game)
{
    int fd;
    int i;

    fd = open_file(arg, game);
    get_height_map(fd, game);

    game->map.file = malloc(sizeof(char *) * (game->map.height_file + 1));
    if (!game->map.file)
    {
        report_err(MALLOC_ERR);
        close(fd);
        free_function(game);
        exit(EXIT_FAILURE);
    }

    i = 0;
    while (i <= game->map.height_file)
    {
        game->map.file[i] = NULL;
        i++;
    }

    fill_file_grid(arg, game);
}

/**
 * @brief Validates and parses the given .cub file.
 *
 * Checks the file extension, loads the file, and processes
 * the map elements and structure.
 *
 * @param arg Path to the .cub file.
 * @param game Pointer to the main game structure.
 */
void parse_arg(char *arg, t_game *game)
{
    int ln;

    ln = ft_strlen(arg);
    if (!(arg[ln - 1] == 'b' && arg[ln - 2] == 'u' && arg[ln - 3] == 'c' &&
          arg[ln - 4] == '.'))
    {
        report_err(SYNTAX_ERR);
        free_function(game);
        exit(EXIT_FAILURE);
    }

    load_file(arg, game);
    parse_elements(game);
    parse_map(game);
}

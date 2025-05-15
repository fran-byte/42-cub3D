/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 23:43:36 by frromero          #+#    #+#             */
/*   Updated: 2025/05/15 18:57:19 by frromero         ###   ########.fr       */
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
 * @param data Pointer to the main game structure.
 */
static void util_exit_fill_file_grid(int fd, t_game *data)
{
    report_err(MALLOC_ERR);
    close(fd);
    free_function(data);
    exit(EXIT_FAILURE);
}

/**
 * @brief Fills the file grid with lines read from the .cub file.
 *
 * Reads each line from the specified file and stores it in
 * the `data->map.file` array for later parsing.
 *
 * @param arg Path to the .cub file.
 * @param data Pointer to the main game structure.
 */
static void fill_file_grid(char *arg, t_game *data)
{
    char *line;
    int i;
    int fd;
    int len;

    fd = open_file(arg, data);
    i = 0;
    line = get_next_line(fd);

    while (line != NULL && i < data->map.height_file)
    {
        len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';

        data->map.file[i] = malloc(len + 1);
        if (!data->map.file[i])
            util_exit_fill_file_grid(fd, data);

        ft_strlcpy(data->map.file[i], line, len + 1);
        free(line);
        line = get_next_line(fd);
        i++;
    }

    data->map.file[i] = NULL;
    close(fd);
}

/**
 * @brief Calculates the number of lines in the .cub file.
 *
 * Iterates through the file to count how many lines it contains
 * and stores the result in `data->map.height_file`.
 *
 * @param fd File descriptor of the opened file.
 * @param data Pointer to the main game structure.
 */
void get_height_map(int fd, t_game *data)
{
    char *line;

    data->map.height_file = 0;
    line = get_next_line(fd);

    while (line != NULL)
    {
        data->map.height_file++;
        free(line);
        line = get_next_line(fd);
    }

    close(fd);
}

/**
 * @brief Loads the content of the .cub file into memory.
 *
 * Allocates memory for `data->map.file`, calculates the height,
 * and fills the grid with the file's contents.
 *
 * @param arg Path to the .cub file.
 * @param data Pointer to the main game structure.
 */
void load_file(char *arg, t_game *data)
{
    int fd;
    int i;

    fd = open_file(arg, data);
    get_height_map(fd, data);

    data->map.file = malloc(sizeof(char *) * (data->map.height_file + 1));
    if (!data->map.file)
    {
        report_err(MALLOC_ERR);
        close(fd);
        free_function(data);
        exit(EXIT_FAILURE);
    }

    i = 0;
    while (i <= data->map.height_file)
    {
        data->map.file[i] = NULL;
        i++;
    }

    fill_file_grid(arg, data);
}

/**
 * @brief Validates and parses the given .cub file.
 *
 * Checks the file extension, loads the file, and processes
 * the map elements and structure.
 *
 * @param arg Path to the .cub file.
 * @param data Pointer to the main game structure.
 */
void parse_arg(char *arg, t_game *data)
{
    int ln;

    ln = ft_strlen(arg);
    if (!(arg[ln - 1] == 'b' && arg[ln - 2] == 'u' && arg[ln - 3] == 'c' &&
          arg[ln - 4] == '.'))
    {
        report_err(SYNTAX_ERR);
        free_function(data);
        exit(EXIT_FAILURE);
    }

    load_file(arg, data);
    parse_elements(data);
    parse_map(data);
}

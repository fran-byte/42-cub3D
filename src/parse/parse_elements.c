/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:50:04 by frromero          #+#    #+#             */
/*   Updated: 2025/05/14 19:16:35 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void process_textures(t_game *data, int *elem, int *i)
{
    if (ft_strncmp(data->map.file[*i], "NO ", 3) == 0 && !data->elem.north)
    {
        store_path(data, data->map.file[*i], &data->map.paths.north);
        data->elem.north = 1;
        *elem += 1;
    }
    else if (ft_strncmp(data->map.file[*i], "SO ", 3) == 0 && !data->elem.south)
    {
        store_path(data, data->map.file[*i], &data->map.paths.south);
        data->elem.south = 1;
        *elem += 1;
    }
    else if (ft_strncmp(data->map.file[*i], "WE ", 3) == 0 && !data->elem.west)
    {
        store_path(data, data->map.file[*i], &data->map.paths.west);
        data->elem.west = 1;
        *elem += 1;
    }
    else if (ft_strncmp(data->map.file[*i], "EA ", 3) == 0 && !data->elem.east)
    {
        store_path(data, data->map.file[*i], &data->map.paths.east);
        data->elem.east = 1;
        *elem += 1;
    }
}

static void process_colors(t_game *data, int *elem, int *i)
{
    if (ft_strncmp(data->map.file[*i], "F ", 2) == 0 && !data->elem.floor)
    {
        parse_color_line(data, data->map.file[*i]);
        data->elem.floor = 1;
        *elem += 1;
    }
    else if (ft_strncmp(data->map.file[*i], "C ", 2) == 0 &&
             !data->elem.ceiling)
    {
        parse_color_line(data, data->map.file[*i]);
        data->elem.ceiling = 1;
        *elem += 1;
    }
}

static void elements_and_file(t_game *data, int *elem, int *i)
{
    if (*elem != 6)
    {
        report_err(MISSING_ELEMENT_ERR);
        free_function(data);
        exit(EXIT_FAILURE);
    }
    while (data->map.file[*i] && is_empty_line(data->map.file[*i]))
        *i += 1;
    if (!data->map.file[*i])
    {
        report_err(MAP_VOID_ERR);
        free_function(data);
        exit(EXIT_FAILURE);
    }
    data->map.map_start_index = *i;
}
static void parse_error(t_game *data)
{
    report_err(ELEMENT_FORMAT_ERR);
    free_function(data);
    exit(EXIT_FAILURE);
}

void parse_elements(t_game *data)
{
    int i;
    int elem;

    i = 0;
    elem = 0;
    data->elem = (t_elem){0};
    while (data->map.file[i] && elem < 6)
    {
        if (is_empty_line(data->map.file[i]))
        {
            i++;
            continue;
        }
        process_textures(data, &elem, &i);
        process_colors(data, &elem, &i);
        if (elem == 0 ||
            (!data->elem.north && !data->elem.south && !data->elem.west &&
             !data->elem.east && !data->elem.floor && !data->elem.ceiling))
            parse_error(data);
        i++;
    }
    elements_and_file(data, &elem, &i);
}

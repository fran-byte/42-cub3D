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

static void exit_error_color(t_game *data, char **grid)
{
    if (grid)
        free_split(grid);
    report_err(FORMAT_COLOR_ERR);
    free_function(data);
    exit(EXIT_FAILURE);
}

static int is_numeric(char *str)
{
    while (*str)
    {
        if (!ft_isdigit(*str))
            return (0);
        str++;
    }
    return (1);
}

void parse_color_line(t_game *data, char *line)
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
        exit_error_color(data, rgb);
    if (!is_numeric(rgb[0]) || !is_numeric(rgb[1]) || !is_numeric(rgb[2]))
        exit_error_color(data, rgb);
    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        exit_error_color(data, rgb);
    free_split(rgb);
}

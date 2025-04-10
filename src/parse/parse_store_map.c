/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_store_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:29:10 by frromero          #+#    #+#             */
/*   Updated: 2025/04/10 18:31:15 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void store_path(t_game *data, char *line, char **dest)
{
	char *path;

	path = ft_strtrim(line + 2, " \t");
	if (!path)
	{
		report_err(MALLOC_ERR);
		free_function(data);
		exit(EXIT_FAILURE);
	}
	if (access(path, R_OK) != 0)
	{
		free(path);
		report_err(TEXTURE_FILE_ERR);
		free_function(data);
		exit(EXIT_FAILURE);
	}
	*dest = path;
}

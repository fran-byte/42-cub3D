/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:32:50 by frromero          #+#    #+#             */
/*   Updated: 2025/04/07 16:36:50 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int open_file(char *arg, t_game *data)
{
	int fd;

	fd = open(arg, O_RDONLY);
	if (fd < 0)
	{
		report_err(OPEN_FILE_ERR);
		free_function(data);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

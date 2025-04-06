/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:32:50 by frromero          #+#    #+#             */
/*   Updated: 2025/04/06 19:34:22 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int open_file(char *arg)
{
	int fd;

	fd = open(arg, O_RDONLY);
	if (fd < 0)
	{
		report_err(OPEN_FILE_ERR);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 23:43:36 by frromero          #+#    #+#             */
/*   Updated: 2025/04/06 18:23:39 by frromero         ###   ########.fr       */
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

int parse_arg(char *arg, t_game *data)
{
	int ln;
	int fd;

	fd = -1;
	ln = ft_strlen(arg);
	if (!(arg[ln - 1] == 'b' && arg[ln - 2] == 'u' && arg[ln - 3] == 'c' && arg[ln - 4] == '.'))
		return (report_err(SYNTAX_ERR), 1);
	if (load_map(arg, data) == -1)
		return (-1);
	return (fd);
}

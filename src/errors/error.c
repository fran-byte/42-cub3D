/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:46:15 by frromero          #+#    #+#             */
/*   Updated: 2025/05/15 19:11:19 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Prints an error message to the standard output.
 *
 * @param str The error message to print.
 * @return Always returns 1.
 */
int	report_err(char *str)
{
	printf("Error\n%s\n", str);
	return (1);
}

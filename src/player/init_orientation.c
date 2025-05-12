/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_orientation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:19:58 by user              #+#    #+#             */
/*   Updated: 2025/05/12 22:31:00 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Asigna los vectores de dirección y plano cuando el jugador mira al NORTE */
static void set_north(t_game *p)
{
    /** VECTOR Dirección:
     hacia arriba en el eje Y (en gráficos Y aumenta hacia abajo) */
    p->player.dir_x = 0;  // Sin componente horizontal
    p->player.dir_y = -1; // Componente vertical negativo (Norte)

    /*PLANO DE CAMARA
    perpendicular a la dirección (apuntando a la derecha) */
    p->player.plane_x = FOV_COEF; // Define el campo de visión horizontal (0.66)
    p->player.plane_y = 0;        // Sin componente vertical en el plano
}

/* Asigna los vectores cuando el jugador mira al SUR */
static void set_south(t_game *p)
{
    // Dirección: hacia abajo en el eje Y
    p->player.dir_x = 0; // Sin componente horizontal
    p->player.dir_y = 1; // Componente vertical positivo (Sur)

    // Plano perpendicular: apuntando a la izquierda (porque es opuesto al
    // Norte)
    p->player.plane_x = -FOV_COEF; // FOV negativo para lado contrario
    p->player.plane_y = 0;
}

/* Asigna los vectores cuando el jugador mira al ESTE (derecha) */
static void set_east(t_game *p)
{
    // Dirección: hacia la derecha en el eje X
    p->player.dir_x = 1; // Componente horizontal positivo (Este)
    p->player.dir_y = 0; // Sin componente vertical

    // Plano perpendicular: apuntando hacia arriba (relativo al Este)
    p->player.plane_x = 0;
    p->player.plane_y = FOV_COEF; // FOV en eje Y positivo
}

/* Asigna los vectores cuando el jugador mira al OESTE (izquierda) */
static void set_west(t_game *p)
{
    // Dirección: hacia la izquierda en el eje X
    p->player.dir_x = -1; // Componente horizontal negativo (Oeste)
    p->player.dir_y = 0;  // Sin componente vertical

    // Plano perpendicular: apuntando hacia abajo (relativo al Oeste)
    p->player.plane_x = 0;
    p->player.plane_y = -FOV_COEF; // FOV en eje Y negativo
}

/* Inicializa:
   VECTORES de DIRECCIÓN y PLANO de CÁMARA según orientación inicial del
 * jugador */
void init_player_vectors(t_game *p)
{
    // Configuración de la orientación guardada durante el parsing
    if (p->player.player_orientation == NORTH)
        set_north(p);
    else if (p->player.player_orientation == SOUTH)
        set_south(p);
    else if (p->player.player_orientation == EAST)
        set_east(p);
    else if (p->player.player_orientation == WEST)
        set_west(p);
}

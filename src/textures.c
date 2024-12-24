/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: krim <krim@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/23 23:37:36 by krim          #+#    #+#                 */
/*   Updated: 2024/12/24 19:59:01 by krim          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Loads all textures using MLX and populates the textures structure.
 * 
 * @param game Pointer to the game structure containing texture paths and MLX instance.
 */
void load_textures(t_game *game)
{
    const char *texture_names[4] = { "NO", "SO", "WE", "EA" };
    int i;

    for (i = 0; i < 4; i++)
    {
        game->textures[i].img = mlx_xpm_file_to_image(
            game->mlx,
            game->textures[i].path,
            &game->textures[i].width,
            &game->textures[i].height
        );
        if (!game->textures[i].img)
        {
            char error_msg[256];
            snprintf(error_msg, sizeof(error_msg), "Failed to load %s texture from path: %s", 
                     texture_names[i], game->textures[i].path);
            error_exit(error_msg);
        }

        game->textures[i].addr = mlx_get_data_addr(
            game->textures[i].img,
            &game->textures[i].bpp,
            &game->textures[i].line_length,
            &game->textures[i].endian
        );
        if (!game->textures[i].addr)
        {
            char error_msg[256];
            snprintf(error_msg, sizeof(error_msg), "Failed to get data address for %s texture", 
                     texture_names[i]);
            error_exit(error_msg);
        }
    }
}


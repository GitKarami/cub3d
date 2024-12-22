/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/22 13:54:16 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/12/22 14:19:44 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int initialize_game(t_game *game, const char *map_file) {
    // Initialize MLX
    game->mlx = mlx_init();
    if (!game->mlx)
        error_exit("MLX initialization failed");

    // Create window
    game->window = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
    if (!game->window)
        error_exit("Window creation failed");

    // Parse the map
    parse_map(game, map_file);

    // Load textures
    load_textures(game);

    // Set initial player position and orientation
    locate_player(game);

    return 0;
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/22 15:14:34 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/12/23 22:41:46 by krim          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void  error_exit(const char *message)
{
	printf("Error\n%s\n", message);
	exit(1);
}
int cleanup_game(t_game *game) {
    // Free texture paths
    for (int i = 0; i < 4; i++) {
        if (game->textures[i].path)
            free(game->textures[i].path);
        if (game->textures[i].img)
            mlx_destroy_image(game->mlx, game->textures[i].img);
    }

    // Free image
    if (game->img.img)
        mlx_destroy_image(game->mlx, game->img.img);
    
    // Free map grid
    if (game->map.grid) {
        for (int y = 0; y < game->map.height; y++) {
            if (game->map.grid[y])
                free(game->map.grid[y]);
        }
        free(game->map.grid);
    }

    // Destroy window
    if (game->window)
        mlx_destroy_window(game->mlx, game->window);
    
    // Destroy MLX instance
    if (game->mlx) {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }
    
    // Free the game structure itself
    free(game);
    
    return 0;
}

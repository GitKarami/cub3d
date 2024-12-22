/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/22 15:14:34 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/12/22 15:16:56 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cleanup_game(t_game *game)
{
	// Free the map grid
	for (int i = 0; i < game->map.height; i++)
		free(game->map.grid[i]);
	free(game->map.grid);

	// Free the textures
	for (int i = 0; i < 4; i++)
		free(game->textures[i].path);

	// Destroy the window and MLX instance
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	return (0);
}

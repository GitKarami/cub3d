/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: krim <krim@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/23 21:59:01 by krim          #+#    #+#                 */
/*   Updated: 2024/12/23 22:28:27 by krim          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	locate_player(t_game *game)
{
    int	y;
    int	x;
    int	player_found;

    y = 0;
    player_found = 0;
    while (y < game->map.height)
    {
        x = 0;
        while (x < game->map.width)
        {
            if (game->map.grid[y][x] == PLAYER_N ||
                game->map.grid[y][x] == PLAYER_S ||
                game->map.grid[y][x] == PLAYER_E ||
                game->map.grid[y][x] == PLAYER_W)
            {
                if (player_found)
                    error_exit("Multiple player starting positions detected.");
                
                // Set player's position to the center of the cell
                game->player.posX = x + 0.5;
                game->player.posY = y + 0.5;
                player_found = 1;

                // Set player direction and camera plane based on orientation
                if (game->map.grid[y][x] == PLAYER_N)
                {
                    game->player.dirX = 0;
                    game->player.dirY = -1;
                    game->player.planeX = 0.66;
                    game->player.planeY = 0;
                }
                else if (game->map.grid[y][x] == PLAYER_S)
                {
                    game->player.dirX = 0;
                    game->player.dirY = 1;
                    game->player.planeX = -0.66;
                    game->player.planeY = 0;
                }
                else if (game->map.grid[y][x] == PLAYER_E)
                {
                    game->player.dirX = 1;
                    game->player.dirY = 0;
                    game->player.planeX = 0;
                    game->player.planeY = 0.66;
                }
                else if (game->map.grid[y][x] == PLAYER_W)
                {
                    game->player.dirX = -1;
                    game->player.dirY = 0;
                    game->player.planeX = 0;
                    game->player.planeY = -0.66;
                }

                // Replace the player's starting position with '0' to mark it as empty space
                game->map.grid[y][x] = EMPTY;
            }
            x++;
        }
        y++;
    }
    if (!player_found)
        error_exit("No player starting position found in the map.");
}
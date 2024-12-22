/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keypress.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/22 14:20:49 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/12/22 15:16:17 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keypress(int key, t_game *game)
{
    double	newPosX;
    double	newPosY;
    double	oldDirX;
    double	oldPlaneX;

    if (key == KEY_ESC)
        cleanup_game(game);
    // Move Forward
    if (key == KEY_W)
    {
        newPosX = game->player.posX + game->player.dirX * MOVE_SPEED;
        newPosY = game->player.posY + game->player.dirY * MOVE_SPEED;
        if (game->map.grid[(int)newPosY][(int)(game->player.posX)] != WALL)
            game->player.posY = newPosY;
        if (game->map.grid[(int)(game->player.posY)][(int)newPosX] != WALL)
            game->player.posX = newPosX;
    }
    // Move Backward
    if (key == KEY_S)
    {
        newPosX = game->player.posX - game->player.dirX * MOVE_SPEED;
        newPosY = game->player.posY - game->player.dirY * MOVE_SPEED;
        if (game->map.grid[(int)newPosY][(int)(game->player.posX)] != WALL)
            game->player.posY = newPosY;
        if (game->map.grid[(int)(game->player.posY)][(int)newPosX] != WALL)
            game->player.posX = newPosX;
    }
    // Strafe Left
    if (key == KEY_A)
    {
        newPosX = game->player.posX - game->player.planeX * MOVE_SPEED;
        newPosY = game->player.posY - game->player.planeY * MOVE_SPEED;
        if (game->map.grid[(int)newPosY][(int)(game->player.posX)] != WALL)
            game->player.posY = newPosY;
        if (game->map.grid[(int)(game->player.posY)][(int)newPosX] != WALL)
            game->player.posX = newPosX;
    }
    // Strafe Right
    if (key == KEY_D)
    {
        newPosX = game->player.posX + game->player.planeX * MOVE_SPEED;
        newPosY = game->player.posY + game->player.planeY * MOVE_SPEED;
        if (game->map.grid[(int)newPosY][(int)(game->player.posX)] != WALL)
            game->player.posY = newPosY;
        if (game->map.grid[(int)(game->player.posY)][(int)newPosX] != WALL)
            game->player.posX = newPosX;
    }
    // Rotate Left
    if (key == KEY_LEFT)
    {
        oldDirX = game->player.dirX;
        game->player.dirX = game->player.dirX * cos(ROT_SPEED) - game->player.dirY * sin(ROT_SPEED);
        game->player.dirY = oldDirX * sin(ROT_SPEED) + game->player.dirY * cos(ROT_SPEED);
        oldPlaneX = game->player.planeX;
        game->player.planeX = game->player.planeX * cos(ROT_SPEED) - game->player.planeY * sin(ROT_SPEED);
        game->player.planeY = oldPlaneX * sin(ROT_SPEED) + game->player.planeY * cos(ROT_SPEED);
    }
    // Rotate Right
    if (key == KEY_RIGHT)
    {
        oldDirX = game->player.dirX;
        game->player.dirX = game->player.dirX * cos(-ROT_SPEED) - game->player.dirY * sin(-ROT_SPEED);
        game->player.dirY = oldDirX * sin(-ROT_SPEED) + game->player.dirY * cos(-ROT_SPEED);
        oldPlaneX = game->player.planeX;
        game->player.planeX = game->player.planeX * cos(-ROT_SPEED) - game->player.planeY * sin(-ROT_SPEED);
        game->player.planeY = oldPlaneX * sin(-ROT_SPEED) + game->player.planeY * cos(-ROT_SPEED);
    }
    render_frame(game);
    return (0);
}

void	setup_hooks(t_game *game)
{
    mlx_hook(game->window, 2, 1L << 0, handle_keypress, game);
    mlx_hook(game->window, 17, 0, cleanup_game, game);
}


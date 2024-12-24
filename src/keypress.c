/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keypress.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/22 14:20:49 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/12/24 22:53:38 by krim          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	handle_movement(t_game *game, double moveSpeed, double rotSpeed)
{
    double	oldDirX;
    double	oldPlaneX;

    // Move Forward
    if (game->keys.move_forward)
    {
        if (game->map.grid[(int)(game->player.posY)][(int)(game->player.posX + game->player.dirX * moveSpeed)] != WALL)
            game->player.posX += game->player.dirX * moveSpeed;
        if (game->map.grid[(int)(game->player.posY + game->player.dirY * moveSpeed)][(int)(game->player.posX)] != WALL)
            game->player.posY += game->player.dirY * moveSpeed;
    }
    // Move Backward
    if (game->keys.move_backward)
    {
        if (game->map.grid[(int)(game->player.posY)][(int)(game->player.posX - game->player.dirX * moveSpeed)] != WALL)
            game->player.posX -= game->player.dirX * moveSpeed;
        if (game->map.grid[(int)(game->player.posY - game->player.dirY * moveSpeed)][(int)(game->player.posX)] != WALL)
            game->player.posY -= game->player.dirY * moveSpeed;
    }
    // Strafe Left
    if (game->keys.move_left)
    {
        if (game->map.grid[(int)(game->player.posY)][(int)(game->player.posX - game->player.planeX * moveSpeed)] != WALL)
            game->player.posX -= game->player.planeX * moveSpeed;
        if (game->map.grid[(int)(game->player.posY - game->player.planeY * moveSpeed)][(int)(game->player.posX)] != WALL)
            game->player.posY -= game->player.planeY * moveSpeed;
    }
    // Strafe Right
    if (game->keys.move_right)
    {
        if (game->map.grid[(int)(game->player.posY)][(int)(game->player.posX + game->player.planeX * moveSpeed)] != WALL)
            game->player.posX += game->player.planeX * moveSpeed;
        if (game->map.grid[(int)(game->player.posY + game->player.planeY * moveSpeed)][(int)(game->player.posX)] != WALL)
            game->player.posY += game->player.planeY * moveSpeed;
    }
    // Rotate Left
    if (game->keys.rotate_right)
    {
        oldDirX = game->player.dirX;
        game->player.dirX = game->player.dirX * cos(rotSpeed) - game->player.dirY * sin(rotSpeed);
        game->player.dirY = oldDirX * sin(rotSpeed) + game->player.dirY * cos(rotSpeed);
        oldPlaneX = game->player.planeX;
        game->player.planeX = game->player.planeX * cos(rotSpeed) - game->player.planeY * sin(rotSpeed);
        game->player.planeY = oldPlaneX * sin(rotSpeed) + game->player.planeY * cos(rotSpeed);
    }
    // Rotate Right
    if (game->keys.rotate_left)
    {
        oldDirX = game->player.dirX;
        game->player.dirX = game->player.dirX * cos(-rotSpeed) - game->player.dirY * sin(-rotSpeed);
        game->player.dirY = oldDirX * sin(-rotSpeed) + game->player.dirY * cos(-rotSpeed);
        oldPlaneX = game->player.planeX;
        game->player.planeX = game->player.planeX * cos(-rotSpeed) - game->player.planeY * sin(-rotSpeed);
        game->player.planeY = oldPlaneX * sin(-rotSpeed) + game->player.planeY * cos(-rotSpeed);
    }
}

int	toggle_keypress(int key, t_game *game)
{
    if (key == KEY_ESC)
        cleanup_game(game);
    if (key == KEY_W)
        game->keys.move_forward = 1;
    if (key == KEY_S)
        game->keys.move_backward = 1;
    if (key == KEY_A)
        game->keys.move_left = 1;
    if (key == KEY_D)
        game->keys.move_right = 1;
    if (key == KEY_LEFT)
        game->keys.rotate_left = 1;
    if (key == KEY_RIGHT)
        game->keys.rotate_right = 1;
    return (0);
}

// Handle key release events by resetting the corresponding key state
int	toggle_keyrelease(int key, t_game *game)
{
    if (key == KEY_W)
        game->keys.move_forward = 0;
    if (key == KEY_S)
        game->keys.move_backward = 0;
    if (key == KEY_A)
        game->keys.move_left = 0;
    if (key == KEY_D)
        game->keys.move_right = 0;
    if (key == KEY_LEFT)
        game->keys.rotate_left = 0;
    if (key == KEY_RIGHT)
        game->keys.rotate_right = 0;
    return (0);
}

void	setup_hooks(t_game *game)
{
    mlx_hook(game->window, 2, 1L << 0, toggle_keypress, game);
    mlx_hook(game->window, 3, 1L << 1, toggle_keyrelease, game);
    mlx_hook(game->window, 17, 0, cleanup_game, game);
    mlx_loop_hook(game->mlx, game_loop, game); 
}


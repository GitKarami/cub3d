/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/22 14:21:32 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/12/24 02:03:14 by krim          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vertical_line(t_game *game, int x, int start, int end, int color)
{
    int	y;

    y = start;
    while (y < end)
    {
        // Calculate the memory address for the pixel
        char *pixel = game->img.addr + (y * game->img.line_length + x * (game->img.bits_per_pixel / 8));
        *(unsigned int*)pixel = color;
        y++;
    }
}

void	render_ceiling(t_game *game, int x, int drawStart)
{
    int y;
    unsigned int ceiling_color = (game->ceiling_color.r << 16) | (game->ceiling_color.g << 8) | game->ceiling_color.b;

    y = 0;
    while (y < drawStart)
    {
        // Ensure y is within the window bounds
        if (y >= 0 && y < WIN_HEIGHT)
        {
            // Calculate the memory address for the pixel
            char *pixel = game->img.addr + (y * game->img.line_length + x * (game->img.bits_per_pixel / 8));
            *(unsigned int*)pixel = ceiling_color;
        }
        y++;
    }
}

void	render_floor(t_game *game, int x, int drawEnd)
{
    int y;
    unsigned int floor_color = (game->floor_color.r << 16) | (game->floor_color.g << 8) | game->floor_color.b;

    y = drawEnd + 1;
    while (y < WIN_HEIGHT)
    {
        // Ensure y is within the window bounds
        if (y >= 0 && y < WIN_HEIGHT)
        {
            // Calculate the memory address for the pixel
            char *pixel = game->img.addr + (y * game->img.line_length + x * (game->img.bits_per_pixel / 8));
            *(unsigned int*)pixel = floor_color;
        }
        y++;
    }
}

void	render_frame(t_game *game)
{
    int x;
    
    x = 0;
    while (x < WIN_WIDTH)
    {
        // Calculate ray position and direction
        double cameraX = 2 * x / (double)WIN_WIDTH - 1;
        double rayDirX = game->player.dirX + game->player.planeX * cameraX;
        double rayDirY = game->player.dirY + game->player.planeY * cameraX;
        
        // Which box of the map we're in
        int mapX = (int)game->player.posX;
        int mapY = (int)game->player.posY;
        
        // Length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;
        
        // Length of ray from one x or y-side to next x or y-side
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        double perpWallDist;
        
        // What direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;
        
        int hit = 0; // Was there a wall hit?
        int side; // Was a NS or a EW wall hit?
        
        // Calculate step and initial sideDist
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (game->player.posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->player.posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (game->player.posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->player.posY) * deltaDistY;
        }
        
        // Perform DDA
        while (hit == 0)
        {
            // Jump to next map square, either in x-direction or y-direction
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            // Check if ray has hit a wall
            if (game->map.grid[mapY][mapX] == '1')
                hit = 1;
        }
        
        // Calculate distance projected on camera direction
        if (side == 0)
            perpWallDist = (mapX - game->player.posX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - game->player.posY + (1 - stepY) / 2) / rayDirY;
        
        // Calculate height of line to draw on screen
        int lineHeight = (int)(WIN_HEIGHT / perpWallDist);
        
        // Calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
        if(drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
        if(drawEnd >= WIN_HEIGHT) drawEnd = WIN_HEIGHT - 1;
        render_ceiling(game, x, drawStart); 
        // Choose wall color
        int color;
        if (side == 1)
            color = 0xFFB6C1; // Red for NS walls
        else
            color = 0xADD8E6; // Green for EW walls
        
        // Draw the vertical line
        draw_vertical_line(game, x, drawStart, drawEnd, color);
        render_floor(game, x, drawEnd);
        x++;
    }
    
    // Put the image to the window
    mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);
}

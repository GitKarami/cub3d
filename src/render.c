/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/22 14:21:32 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/12/24 22:58:49 by krim          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_textured_line(t_game *game, int x, int start, int end, t_texture *texture, double step, double texPos, int texX, int side)
{
    int	y;

    y = start;
    while (y < end)
    {
        // Ensure y is within the window bounds
        if (y >= 0 && y < WIN_HEIGHT)
        {
            // Calculate the texture y-coordinate
            int texY = (int)texPos & (texture->height - 1);
            texPos += step;
            
            // Get the color from the texture
            char *texture_pixel = texture->addr + (texY * texture->line_length + texX * (texture->bpp / 8));
            unsigned int color = *(unsigned int*)texture_pixel;

            // Apply simple shading for NS walls 
            if (side == 1)
                color = (color >> 1) & 8355711; // Darken the color

            // Calculate the memory address for the pixel on the screen
            char *pixel = game->img.addr + (y * game->img.line_length + x * (game->img.bits_per_pixel / 8));
            *(unsigned int*)pixel = color;
        }
        y++;
    }
}

t_texture	*select_texture(t_game *game, int side, double rayDirX, double rayDirY)
{
    if (side == 0) // EW walls
    {
        if (rayDirX > 0)
            return &game->textures[3]; // East
        else
            return &game->textures[2]; // West
    }
    else // NS walls
    {
        if (rayDirY > 0)
            return &game->textures[1]; // South
        else
            return &game->textures[0]; // North
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

void	init_ray(t_game *game, int x, double *cameraX, double *rayDirX, double *rayDirY)
{
    *cameraX = 2.0 * x / (double)WIN_WIDTH - 1.0;
    *rayDirX = game->player.dirX + game->player.planeX * (*cameraX);
    *rayDirY = game->player.dirY + game->player.planeY * (*cameraX);
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
        t_texture *current_texture = select_texture(game, side, rayDirX, rayDirY);
        double wallX; // Where exactly the wall was hit
        if (side == 0)
            wallX = game->player.posY + perpWallDist * rayDirY;
        else
            wallX = game->player.posX + perpWallDist * rayDirX;
        wallX -= floor(wallX);
        
        // Calculate the x coordinate on the texture
        int texX = (int)(wallX * (double)current_texture->width);
        if(side == 0 && rayDirX > 0)
            texX = current_texture->width - texX - 1;
        if(side == 1 && rayDirY < 0)
            texX = current_texture->width - texX - 1;
        // Ensure texX is within texture bounds
        if (texX < 0)
            texX = 0;
        if (texX >= current_texture->width)
            texX = current_texture->width - 1;
        
        // Calculate step and initial texture position for y
        double step = 1.0 * current_texture->height / lineHeight;
        double texPos = (drawStart - WIN_HEIGHT / 2 + lineHeight / 2) * step;
        
        // Draw the textured vertical line
        draw_textured_line(game, x, drawStart, drawEnd, current_texture, step, texPos, texX, side);
        render_floor(game, x, drawEnd);
        // debug_info(game, x, cameraX, rayDirX, rayDirY, mapX, mapY, perpWallDist, drawStart, drawEnd, side);
        x++;
    }
    
    // Put the image to the window
    mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);
}

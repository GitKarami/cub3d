/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/22 14:21:32 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/12/25 00:30:28 by krim          ########   odam.nl         */
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

static void	initialize_ray(t_game *game, int x, double *cameraX, double *rayDirX, double *rayDirY)
{
    *cameraX = 2.0 * x / (double)WIN_WIDTH - 1.0;
    *rayDirX = game->player.dirX + game->player.planeX * (*cameraX);
    *rayDirY = game->player.dirY + game->player.planeY * (*cameraX);
}

static void	calculate_step_side(t_game *game, double rayDirX, double rayDirY, int mapX, int mapY, int *stepX, int *stepY, double *sideDistX, double *sideDistY, double deltaDistX, double deltaDistY)
{
    if (rayDirX < 0)
    {
        *stepX = -1;
        *sideDistX = (game->player.posX - mapX) * deltaDistX;
    }
    else
    {
        *stepX = 1;
        *sideDistX = (mapX + 1.0 - game->player.posX) * deltaDistX;
    }
    if (rayDirY < 0)
    {
        *stepY = -1;
        *sideDistY = (game->player.posY - mapY) * deltaDistY;
    }
    else
    {
        *stepY = 1;
        *sideDistY = (mapY + 1.0 - game->player.posY) * deltaDistY;
    }
}

static void	perform_dda(t_game *game, int *mapX, int *mapY, double *sideDistX, double *sideDistY, double deltaDistX, double deltaDistY, int stepX, int stepY, int *side)
{
    int hit = 0;

    while (hit == 0)
    {
        if (*sideDistX < *sideDistY)
        {
            *sideDistX += deltaDistX;
            *mapX += stepX;
            *side = 0;
        }
        else
        {
            *sideDistY += deltaDistY;
            *mapY += stepY;
            *side = 1;
        }
        if (game->map.grid[*mapY][*mapX] == '1')
            hit = 1;
    }
}

static double	calculate_perp_wall_dist(t_game *game, int side, double rayDirX, double rayDirY, int mapX, int mapY, int stepX, int stepY)
{
    double perpWallDist;

    if (side == 0)
        perpWallDist = (mapX - game->player.posX + (1 - stepX) / 2) / rayDirX;
    else
        perpWallDist = (mapY - game->player.posY + (1 - stepY) / 2) / rayDirY;
    return perpWallDist;
}

static void	calculate_texture(t_game *game, int side, double rayDirX, double rayDirY, double perpWallDist, double *wallX, int *texX, t_texture **current_texture)
{
    *current_texture = select_texture(game, side, rayDirX, rayDirY);
    if (side == 0)
        *wallX = game->player.posY + perpWallDist * rayDirY;
    else
        *wallX = game->player.posX + perpWallDist * rayDirX;
    *wallX -= floor(*wallX);
    *texX = (int)(*wallX * (double)(*current_texture)->width);
    if (side == 0 && rayDirX > 0)
        *texX = (*current_texture)->width - *texX - 1;
    if (side == 1 && rayDirY < 0)
        *texX = (*current_texture)->width - *texX - 1;
    if (*texX < 0)
        *texX = 0;
    if (*texX >= (*current_texture)->width)
        *texX = (*current_texture)->width - 1;
}

static void	calculate_step_texPos(int lineHeight, t_texture *current_texture, double *step, double *texPos, int drawStart)
{
    *step = 1.0 * current_texture->height / lineHeight;
    *texPos = (drawStart - WIN_HEIGHT / 2 + lineHeight / 2) * (*step);
}

void	render_frame(t_game *game)
{
    int		x;
    double	cameraX;
    double	rayDirX;
    double	rayDirY;
    int		mapX;
    int		mapY;
    double	deltaDistX;
    double	deltaDistY;
    int		stepX;
    int		stepY;
    int		side;
    double	sideDistX;
    double	sideDistY;
    double	perpWallDist;
    int		lineHeight;
    int		drawStart;
    int		drawEnd;
    double	wallX;
    int		texX;
    t_texture	*current_texture;
    double	step;
    double	texPos;

    x = 0;
    while (x < WIN_WIDTH)
    {
        initialize_ray(game, x, &cameraX, &rayDirX, &rayDirY);
        mapX = (int)game->player.posX;
        mapY = (int)game->player.posY;
        deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        calculate_step_side(game, rayDirX, rayDirY, mapX, mapY, &stepX, &stepY, &sideDistX, &sideDistY, deltaDistX, deltaDistY);
        perform_dda(game, &mapX, &mapY, &sideDistX, &sideDistY, deltaDistX, deltaDistY, stepX, stepY, &side);
        perpWallDist = calculate_perp_wall_dist(game, side, rayDirX, rayDirY, mapX, mapY, stepX, stepY);
        lineHeight = (int)(WIN_HEIGHT / perpWallDist);
        drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;
        drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
        if (drawEnd >= WIN_HEIGHT)
            drawEnd = WIN_HEIGHT - 1;
        render_ceiling(game, x, drawStart);
        calculate_texture(game, side, rayDirX, rayDirY, perpWallDist, &wallX, &texX, &current_texture);
        calculate_step_texPos(lineHeight, current_texture, &step, &texPos, drawStart);
        draw_textured_line(game, x, drawStart, drawEnd, current_texture, step, texPos, texX, side);
        render_floor(game, x, drawEnd);
        x++;
    }
    mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/22 13:54:16 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/12/24 22:56:09 by krim          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx_image(t_game *game)
{
    game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
    if (!game->img.img)
        error_exit("Failed to create image");
    
    game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_length, &game->img.endian);
    if (!game->img.addr)
        error_exit("Failed to get image data address");
}

void    init_player(t_player *player) {
    player->posX = 0;
    player->posY = 0;
    player->dirX = -1;
    player->dirY = 0;
    player->planeX = 0;
    player->planeY = 0.66;
}

void init_keys(t_movement *keys) {
    keys->move_forward = 0;
    keys->move_backward = 0;
    keys->move_left = 0;
    keys->move_right = 0;
    keys->rotate_left = 0;
    keys->rotate_right = 0;
}

void init_textures(t_game *game)
{
    int i;

    i = 0;
    while (i < 4)
    {
        game->textures[i].path = NULL;
        game->textures[i].img = NULL;
        game->textures[i].width = 0;
        game->textures[i].height = 0;
        game->textures[i].addr = NULL;
        game->textures[i].bpp = 0;
        game->textures[i].line_length = 0;
        game->textures[i].endian = 0;
        i++;
    }
}

void init_image(t_game *game) {
    game->img.img = NULL;
    game->img.addr = NULL;
    game->img.bits_per_pixel = 0;
    game->img.line_length = 0;
    game->img.endian = 0;
}

void init_map(t_game *game) {
    game->map.grid = NULL;
    game->map.width = 0;
    game->map.height = 0;
}

void init_game(t_game *game) {
    game->mlx = NULL;
    game->window = NULL;
    init_player(&game->player);
    init_textures(game);
    init_image(game);
    init_keys(&game->keys);
    init_map(game);
}

int initialize_game(t_game *game, const char *map_file)
{
    (void)map_file;
    init_game(game);
    game->mlx = mlx_init();
    if (!game->mlx)
        error_exit("MLX initialization failed");

    // Create window
    game->window = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
    if (!game->window)
        error_exit("Window creation failed");

    // Parse the map
    parse_map(game, map_file);

    load_textures(game);

    // locate_player(game);

    return 0;
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/22 13:50:08 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/12/23 23:45:39 by krim          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>

void print_game_struct(const t_game *game)
{
    printf("=== Game Structure ===\n\n");

    // MLX and Window Pointers
    printf("--- MLX and Window ---\n");
    printf("MLX Instance Pointer: %p\n", game->mlx);
    printf("Window Pointer: %p\n\n", game->window);

    // Player Information
    printf("--- Player ---\n");
    printf("Position: (x: %.2f, y: %.2f)\n", game->player.posX, game->player.posY);
    printf("Direction Vector: (x: %.2f, y: %.2f)\n", game->player.dirX, game->player.dirY);
    printf("Camera Plane: (x: %.2f, y: %.2f)\n\n", game->player.planeX, game->player.planeY);

    // Textures Information
    printf("--- Textures ---\n");
    const char *texture_names[4] = { "NO", "SO", "WE", "EA" };
    for (int i = 0; i < 4; i++)
    {
        printf("Texture %s:\n", texture_names[i]);
        printf("  Path: %s\n", game->textures[i].path ? game->textures[i].path : "NULL");
        printf("  Image Pointer: %p\n", game->textures[i].img);
        printf("  Width: %d\n", game->textures[i].width);
        printf("  Height: %d\n", game->textures[i].height);
        printf("  Address: %p\n", game->textures[i].addr);
        printf("  Bits Per Pixel: %d\n", game->textures[i].bpp);
        printf("  Line Length: %d\n", game->textures[i].line_length);
        printf("  Endian: %d\n\n", game->textures[i].endian);
    }

    // Floor and Ceiling Colors
    printf("--- Colors ---\n");
    printf("Floor Color: RGB(%d, %d, %d)\n", game->floor_color.r, game->floor_color.g, game->floor_color.b);
    printf("Ceiling Color: RGB(%d, %d, %d)\n\n", game->ceiling_color.r, game->ceiling_color.g, game->ceiling_color.b);

    // Map Information
    printf("--- Map ---\n");
    printf("Map Width: %d\n", game->map.width);
    printf("Map Height: %d\n", game->map.height);
    printf("Map Grid:\n");
    for (int y = 0; y < game->map.height; y++)
    {
        printf("  %s\n", game->map.grid[y] ? game->map.grid[y] : "NULL");
    }
    printf("\n");

    // Image Information
    printf("--- Image Buffer ---\n");
    printf("Image Pointer: %p\n", game->img.img);
    printf("Address: %p\n", game->img.addr);
    printf("Bits Per Pixel: %d\n", game->img.bits_per_pixel);
    printf("Line Length: %d\n", game->img.line_length);
    printf("Endian: %d\n\n", game->img.endian);

    printf("======================\n");
}
// Function to check if a string ends with a given suffix
int ft_strends_with(const char *str, const char *suffix)
{
    if (!str || !suffix)
        return 0;

    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);

    if (suffix_len > str_len)
        return 0;

    return (strcmp(str + str_len - suffix_len, suffix) == 0);
}

int	game_loop(t_game *game)
{
	// render_frame(game);
	setup_hooks(game);
	mlx_loop(game->mlx);
	return (0);
}
int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2) {
        error_exit("Usage: ./cub3d <map_file.cub>");
    }

    if (!ft_strends_with(argv[1], MAP_EXT)) {
        error_exit("Map file must have a .cub extension");
    }

    initialize_game(&game, argv[1]);
    print_game_struct(&game);
    game_loop(&game);
    // cleanup_game(&game);
    return 0;
}

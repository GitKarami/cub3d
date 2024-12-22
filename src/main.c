/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/22 13:50:08 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/12/22 15:11:02 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include "cub3d.h"
#include <string.h>

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
	render_frame(game);
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
    game_loop(&game);
    cleanup_game(&game);
    return 0;
}

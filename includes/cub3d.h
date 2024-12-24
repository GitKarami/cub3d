/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/22 13:23:00 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/12/24 22:52:56 by krim          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include "../lib/minilibx/mlx.h"
#include "../lib/libft/libft.h"

// Define window dimensions
#define WIN_WIDTH 800 // Width of the game window
#define WIN_HEIGHT 600 // Height of the game window

// Define movement speed
#define MOVE_SPEED 0.008 // Player movement speed
#define ROT_SPEED 0.006 // Player rotation speed

// Define maximum map size
#define MAX_MAP_WIDTH 100
#define MAX_MAP_HEIGHT 100

// Define file extension for map
#define MAP_EXT ".cub"

// Define allowed map characters
#define WALL '1'
#define EMPTY '0'
#define PLAYER_N 'N'
#define PLAYER_S 'S'
#define PLAYER_E 'E'
#define PLAYER_W 'W'

// Define identifiers for textures and colors
#define IDENT_NO "NO"
#define IDENT_SO "SO"
#define IDENT_WE "WE"
#define IDENT_EA "EA"
#define IDENT_F "F"
#define IDENT_C "C"

// Define key codes for Linux
#define KEY_ESC 65307    // Key code for the ESC key
#define KEY_W 119        // Key code for the W key
#define KEY_A 97         // Key code for the A key
#define KEY_S 115        // Key code for the S key
#define KEY_D 100        // Key code for the D key
#define KEY_LEFT 65361    // Key code for the left arrow key
#define KEY_RIGHT 65363   // Key code for the right arrow key

// Struct for storing player information
typedef struct s_player {
    double posX;   // Player's X position
    double posY;   // Player's Y position
    double dirX;   // Player's direction vector X
    double dirY;   // Player's direction vector Y
    double planeX; // Camera plane X
    double planeY; // Camera plane Y
}               t_player;

typedef struct s_movement {
    int move_forward;
    int move_backward;
    int move_left;
    int move_right;
    int rotate_left;
    int rotate_right;
}               t_movement;
// Struct for storing texture information
typedef struct s_texture {
    char *path;    // Path to the texture file
    void *img;     // MLX image pointer
    int width;     // Texture width
    int height;    // Texture height
    char *addr;    // Image address
    int bpp;       // Bits per pixel
    int line_length;  // Line length
    int endian;    // Endianess
    int tex_x;     // Texture X coordinate
}               t_texture;

// Struct for storing color information
typedef struct s_color {
    int r;         // Red component
    int g;         // Green component
    int b;         // Blue component
}               t_color;

// Struct for storing the map
typedef struct s_map {
    char **grid;    // 2D array representing the map
    int width;      // Width of the map
    int height;     // Height of the map
}               t_map;

// Struct for storing image information
typedef struct s_image {
    void *img;             // MLX image pointer
    char *addr;            // Image address
    int bits_per_pixel;    // Bits per pixel
    int line_length;       // Line length
    int endian;            // Endianess
}               t_image;

// Struct for the game state
typedef struct s_game {
    void *mlx;               // MLX instance
    void *window;            // MLX window
    t_player player;         // Player information
    t_texture textures[4];   // Array for NO, SO, WE, EA textures
    t_color floor_color;     // Floor color
    t_color ceiling_color;   // Ceiling color
    t_map map;               // Game map
    t_image img;             // Image buffer for rendering
    t_movement keys;         // Movement keys
    // Add more game-related variables here
}               t_game;

// Function prototypes

// Initialization functions
int     initialize_game(t_game *game, const char *map_file);
void	init_mlx_image(t_game *game);

// Rendering functions
void    render_frame(t_game *game);
void    draw_vertical_line(t_game *game, int x, int start, int end, int color);

// Input handling functions
void	handle_movement(t_game *game, double moveSpeed, double rotSpeed);
int     handle_keyrelease(int key, t_game *game);
void	setup_hooks(t_game *game);

// Game loop
int     game_loop(t_game *game);

// Map parsing functions
int     parse_map(t_game *game, const char *filepath);
int     validate_map(t_game *game);
void    locate_player(t_game *game);
int     parse_map_grid(t_game *game, char **map_lines, int line_count);
int     parse_config(t_game *game, char *line);

// Texture loading functions
void    load_textures(t_game *game);

// Color parsing functions
int     parse_colors(t_game *game, char **split);

// Utility functions
void    error_exit(const char *message);
int    cleanup_game(t_game *game);
void    debug_info(t_game *game, int x, double cameraX, double rayDirX, double rayDirY, int mapX, int mapY, double perpWallDist, int drawStart, int drawEnd, int side);

#endif // CUB3D_H


/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kchahmi <kchahmi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/22 14:16:08 by kchahmi       #+#    #+#                 */
/*   Updated: 2024/12/22 15:13:33 by kchahmi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include "cub3d.h"

// Function to check if a character is a whitespace character
int ft_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

int	validate_map(t_game *game)
{
    int	player_count = 0;

    for (int y = 0; y < game->map.height; y++)
    {
        for (int x = 0; x < game->map.width; x++)
        {
            char c = game->map.grid[y][x];
            // Check for player start positions
            if (c == PLAYER_N || c == PLAYER_S || c == PLAYER_E || c == PLAYER_W)
            {
                player_count++;
                if (player_count > 1)
                    error_exit("Multiple player start positions found");

                // Set player position
                game->player.posX = x + 0.5;
                game->player.posY = y + 0.5;

                // Set player direction and camera plane based on orientation
                if (c == PLAYER_N)
                {
                    game->player.dirX = 0;
                    game->player.dirY = -1;
                    game->player.planeX = 0.66;
                    game->player.planeY = 0;
                }
                else if (c == PLAYER_S)
                {
                    game->player.dirX = 0;
                    game->player.dirY = 1;
                    game->player.planeX = -0.66;
                    game->player.planeY = 0;
                }
                else if (c == PLAYER_E)
                {
                    game->player.dirX = 1;
                    game->player.dirY = 0;
                    game->player.planeX = 0;
                    game->player.planeY = 0.66;
                }
                else if (c == PLAYER_W)
                {
                    game->player.dirX = -1;
                    game->player.dirY = 0;
                    game->player.planeX = 0;
                    game->player.planeY = -0.66;
                }
                // Replace player character with empty space
                game->map.grid[y][x] = EMPTY;
            }
            // Validate boundary walls
            if (y == 0 || y == game->map.height -1 || x == 0 || x == game->map.width -1)
            {
                if (c != WALL && c != ' ')
                    error_exit("Map is not enclosed by walls");
            }
            // Validate interior characters
            if (c != WALL && c != EMPTY && c != ' ')
                error_exit("Invalid character in map");
        }
    }

    if (player_count != 1)
        error_exit("Player start position not defined or multiple positions found");

    return 1;
}

static void	allocate_map(t_game *game, char **lines, int line_count)
{
    int	max_width = 0;

    // Determine the maximum width of the map
    for (int i = 0; i < line_count; i++)
    {
        int len = strlen(lines[i]);
        if (len > max_width)
            max_width = len;
    }
    game->map.width = max_width;
    game->map.height = line_count;

    // Allocate the 2D map grid
    game->map.grid = malloc(sizeof(char *) * (line_count + 1));
    if (!game->map.grid)
        error_exit("Memory allocation failed for map grid");

    for (int y = 0; y < line_count; y++)
    {
        game->map.grid[y] = malloc(sizeof(char) * (max_width + 1));
        if (!game->map.grid[y])
            error_exit("Memory allocation failed for map row");

        // Initialize the row with walls ('1')
        for (int x = 0; x < max_width; x++)
            game->map.grid[y][x] = '1';
        game->map.grid[y][max_width] = '\0';

        // Copy the map line into the grid
        for (int x = 0; lines[y][x] != '\0'; x++)
        {
            char c = lines[y][x];
            if (c == ' ' )
                game->map.grid[y][x] = ' ';
            else if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
                game->map.grid[y][x] = c;
            else
                error_exit("Invalid character in map");
        }
    }
    game->map.grid[line_count] = NULL;
}

static char	**read_map_lines(int fd, int line_count)
{
    char	**map = malloc(sizeof(char *) * (line_count + 1));
    int		i = 0;
    char	*line;

    if (!map)
        error_exit("Memory allocation failed for map");

    while (i < line_count && get_next_line(fd, &line) > 0)
    {
        // Skip empty lines
        if (line && line[0] != '\0')
        {
            // Remove trailing newline if present
            char *newline = strchr(line, '\n');
            if (newline)
                *newline = '\0';
            map[i++] = strdup(line);
            if (!map[i - 1])
                error_exit("Memory allocation failed for map line");
        }
        free(line);
    }
    map[i] = NULL;
    return map;
}

static int	count_map_lines(int fd)
{
    int		count;
    char	*line;

    count = 0;
    while (get_next_line(fd, &line) > 0)
    {
        // Check if the line is not empty
        if (line && line[0] != '\0')
            count++;
        free(line);
    }
    // Rewind the file descriptor to start reading map lines
    lseek(fd, 0, SEEK_SET);
    return count;
}

int	parse_map_grid(t_game *game, int fd)
{
    char	**map_lines;
    int		line_count;

    // Count the number of map lines
    line_count = count_map_lines(fd);
    if (line_count <= 0)
        error_exit("No map data found");

    // Allocate memory and read map lines
    map_lines = read_map_lines(fd, line_count);
    if (!map_lines)
        error_exit("Failed to read map lines");

    // Allocate and populate the map grid
    allocate_map(game, map_lines, line_count);

    // Free the temporary map lines
    for (int i = 0; i < line_count; i++)
        free(map_lines[i]);
    free(map_lines);

    // Validate the map structure
    if (!validate_map(game))
        error_exit("Map validation failed");

    return 1;
}

int	parse_color(t_game *game, char *line, t_color *color)
{
	(void)game;
    int	r, g, b;

    // Split the line by commas
    if (sscanf(line, "%d,%d,%d", &r, &g, &b) != 3)
        error_exit("Invalid color format");

    // Validate color ranges
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        error_exit("Color values must be between 0 and 255");

    // Assign colors
    color->r = r;
    color->g = g;
    color->b = b;

    return 1;
}

int	parse_texture(t_game *game, char *line, int texture_index)
{
    // Skip identifier and any additional whitespace
    while (ft_isspace(*line))
        line++;

    // Check if texture path is already set
    if (game->textures[texture_index].path)
        error_exit("Duplicate texture configuration");

    // Allocate and assign the texture path
    game->textures[texture_index].path = strdup(line);
    if (!game->textures[texture_index].path)
        error_exit("Memory allocation failed for texture path");

    return 1;
}

int	parse_config(t_game *game, char *line)
{
    // Skip leading whitespace
    while (ft_isspace(*line))
        line++;

    // Identify the type of configuration
    if (strncmp(line, "NO ", 3) == 0)
        return parse_texture(game, line + 2, 0); // NO texture
    if (strncmp(line, "SO ", 3) == 0)
        return parse_texture(game, line + 2, 1); // SO texture
    if (strncmp(line, "WE ", 3) == 0)
        return parse_texture(game, line + 2, 2); // WE texture
    if (strncmp(line, "EA ", 3) == 0)
        return parse_texture(game, line + 2, 3); // EA texture
    if (strncmp(line, "F ", 2) == 0)
        return parse_color(game, line + 1, &game->floor_color); // Floor color
    if (strncmp(line, "C ", 2) == 0)
        return parse_color(game, line + 1, &game->ceiling_color); // Ceiling color

    // If identifier is not recognized
    error_exit("Invalid configuration identifier");
    return 0;
}

int is_config_line(const char *line)
{
    if (!line)
        return 0;

    // Skip leading whitespace
    while (ft_isspace(*line))
        line++;

    // Check for configuration identifiers
    if (strncmp(line, "NO ", 3) == 0 ||
        strncmp(line, "SO ", 3) == 0 ||
        strncmp(line, "WE ", 3) == 0 ||
        strncmp(line, "EA ", 3) == 0 ||
        strncmp(line, "F ", 2) == 0 ||
        strncmp(line, "C ", 2) == 0)
        return 1;

    return 0;
}

int parse_map(t_game *game, const char *filepath)
{
    // Open the file
    int fd = open(filepath, O_RDONLY);
    if (fd < 0)
        error_exit("Failed to open map file");

    // Read and parse each line
    char *line;
    while (get_next_line(fd, &line) > 0) {
        // Parse configuration lines
        if (is_config_line(line))
            parse_config(game, line);
        else
            break;
        free(line);
    }

    // Parse the map
    parse_map_grid(game, fd);
    close(fd);
    return 0;
}

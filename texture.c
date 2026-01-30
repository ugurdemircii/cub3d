#include "a.h"

void texture(t_game *game, t_values *values, int side, double perp_dist, int line_h, int start, int end, int x)
{
    int y;
    int bpp;          
    int size_line;    
    int endian;       
    int *texture_data;
    double wall_x;
    double text_w;
    int h;
    void *image;
    int value;
    int tex_w;
    int tex_h;
    double tex_pos;
    double step;
    unsigned int color;
    int tex_y;
    int tex_x;

    y = start;
    tex_w = 64;
    tex_h = 64;
    value = 64;
    image = mlx_xpm_file_to_image(game->mlx,"./test.xpm", &value, &value);
    texture_data = (int *)mlx_get_data_addr(image, &bpp, &size_line, &endian);
    h = 448;
    text_w = 64.0;
    if (side == 0) 
        wall_x = values->spos_y + perp_dist * values->raydir_y;
    else           
        wall_x = values->spos_x + perp_dist * values->raydir_x;
    wall_x -= floor((wall_x));
    tex_x = (int)(wall_x * text_w);
    if(side == 0 && values->raydir_x > 0)
        tex_x = text_w - tex_x - 1;
    if(side == 1 && values->raydir_y < 0)
        tex_x = text_w - tex_x - 1;
    step = 1.0 * 64.0 / line_h;
    tex_pos = (start - h / 2 + line_h / 2) * step;
    while(y < end)
    {
        tex_y = (int)tex_pos & (64 - 1);
        tex_pos += step;
        color = texture_data[tex_h * tex_y + tex_x];
        if(side == 1) 
            color = (color >> 1) & 8355711;
        mlx_pixel_put(game->mlx, game->win, x, y, color);
        y++;
    }
}
#include "control_common.hpp"
#include <sstream>
#include <fstream>
#include <string>

using namespace genv;


canvas read_kep(const std::string& fname)
{
    std::ifstream f(fname);
    int width, height;
    f >> width >> height >> std::ws;

    canvas c(width, height); 

    int r, g, b;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            f >> r >> g >> b;

            c << move_to(x, y) 
            << color(r, g, b) 
            << dot;
        }
    }
    c.transparent(true);
    return c;
}

canvas read_matrix(const std::vector<std::vector<int>> matrix, color color)
{
    int max_y = matrix.size();
    int max_x = matrix[0].size();

    canvas c(max_x, max_y);
    c << color;

    for (int y = 0; y < max_y; y++)
    {
        for (int x = 0; x < max_x; x++)
        {
            if (matrix[y][x])
            {
                c << move_to(x, y) << dot;
            }
        }
    }
    c.transparent(true);
    return c;
}

color hex_to_color(int h)
{
    int b = h % 256;
    h /= 256;
    int g = h % 256;
    h /= 256;
    int r = h % 256;
    return color(r, g, b);
}

color change_shade(const color &c, float dr, float dg, float db)
{
    int r = c.red   * dr;
    int g = c.green * dg;
    int b = c.blue  * db;
    return color(std::min(r, 255), std::min(g, 255), std::min(b, 255));
}

color change_shade(const color &c, float d)
{
    return change_shade(c, d, d, d);
}

color change_tint(const color &c, float dr, float dg, float db)
{
    int r = c.red   + (255 - c.red)   * dr;
    int g = c.green + (255 - c.green) * dg;
    int b = c.blue  + (255 - c.blue)  * db;
    return color(std::min(r, 255), std::min(g, 255), std::min(b, 255));
}

color change_tint(const color &c, float d)
{
    return change_tint(c, d, d, d);
}
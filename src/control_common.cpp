#include "control_common.hpp"
#include <sstream>
#include <fstream>
#include <string>

using namespace genv;

namespace Controls
{
    int ENV_WIDTH  = 999999;
    int ENV_HEIGHT = 999999;
    color BACKGROUND_COLOR = color(60, 60, 60);

    canvas read_kep(const std::string& fname)
    {
        std::ifstream f(fname);
        int width, height;
        f >> width >> height >> std::ws;

        canvas c(width, height); 

        int x, y;
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

    color hex_to_color(const std::string& h)
    {
        int n;
        std::istringstream(h) >> std::hex >> n;
        int b = n % 256;
        n/= 256;
        int g = n % 256;
        n /= 256;
        int r = n % 256;
        return color(r, g, b);
    }
}
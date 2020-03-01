#include <sstream>
#include <iostream>
#include <fstream>
#include "pch.hpp"

using namespace genv;

canvas downarrow(int sz, color clr = color(255, 255, 255))
{
    std::ofstream f("out.kep");

    canvas c(2*sz, sz);
    c << clr;
    int margin = 0;
    for (int y = 0; y < sz; y++)
    {
        for (int x = 0; x < 2*sz; x++)
        {
            // std::cout << (sz+x) << " vs " << (2*sz - margin) << '\n';
            if (x <= 2*sz - margin && x >= margin)
            {
                f << "1 0 0\t";
                c << move_to(x, y) << dot;   
            }
            else
            {
                f << "0 0 0\t";
            }
        }
        f << '\n';
        margin++;
    }
    c.transparent(true);
    return c;
}

int main(int argc, char const *argv[])
{
    gout.open(800, 600);

    canvas dnarrow = downarrow(5);
    gout << stamp(dnarrow, 100, 100);

    gout << refresh;

    event ev;
    while(gin >> ev)
    {
    }

    return 0;
}

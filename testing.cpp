#include <sstream>
#include <iostream>
#include "pch.hpp"

using namespace genv;


int main(int argc, char const *argv[])
{
    gout.open(800, 600);

    canvas dnarrow = downarrow(7);
    gout << stamp(dnarrow, 100, 100);

    gout << refresh;

    event ev;
    while(gin >> ev)
    {
    }

    return 0;
}

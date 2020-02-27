#include <sstream>
#include <iostream>
#include "controls.hpp"
#include "pch.hpp"

using namespace Controls;
using namespace genv;

int main(int argc, char const *argv[])
{
    ENV_HEIGHT = 600;
    ENV_WIDTH = 800;
    gout.open(ENV_WIDTH, ENV_HEIGHT);

    event ev;
    while(gin >> ev)
    {
    }

    return 0;
}

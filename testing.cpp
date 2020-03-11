#include "pch.hpp"

using namespace Controls;

int main(int argc, char const *argv[])
{
    Scene s(640, 480);
    TextBox* t = new TextBox(Point(20, 20), "Default text", 150);
    t->set_font("LiberationSans-Regular.ttf");
    s.add_control(t);
    s.run();

    return 0;
}

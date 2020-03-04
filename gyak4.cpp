#include "pch.hpp"
#include "controls.cpp"

using namespace genv;
using namespace Controls;

void style_label(Label*& lbl)
{
    lbl->is_hittest_visible = true;
    lbl->set_font("LiberationSans-Regular.ttf");
    lbl->set_border_thickness(3);
}

// hf.: fogantyú a sarokba, ami átméretezi
int main(int argc, char const *argv[])
{
    Scene s(500, 300);
    for (int i = 0; i < 10; i++)
    {
        int x = std::rand() % 400;
        int y = std::rand() % 200;
        int m_x = 10 + std::rand() % 20;
        int m_y = 5 + std::rand() % 15;
        Label* lbl1 = new Label(Point(x, y), "0", Margin(m_x, m_y));
        style_label(lbl1);
        s.add_control(lbl1);
    }
    s.run();
}

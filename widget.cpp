#include "pch.hpp"
#include "controls.cpp"

using namespace genv;
using namespace Controls;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void print_one()
{
    std::cout << "+1\n";
}

canvas read_kep(const std::string& fname)
{
    std::ifstream f(fname);
    int width, height;
    f >> width >> std::ws;
    f >> height >> std::ws;

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

// HF.: label bal alsó sarkát húzva lehessen átméretezni
void style_btn(Button*& btn)
{
    btn->set_border_color("E5D96E");
    btn->set_text_fill_normal("E5D96E");
    btn->set_normal_bg("6c6c6c");
    btn->set_hover_bg("7c7c7c");
    btn->set_focus_bg("7c7c7c");
    btn->set_drag_bg("8c8c8c");
    btn->set_font("LiberationSans-Regular.ttf");
}

void vmi()
{
    std::cout << "vmi\n";
}

int main(int argc, char const *argv[])
{
    Scene s(SCREEN_WIDTH, SCREEN_HEIGHT);
    for (int i = 0; i < 7; i++)
    {
        int x = std::rand() % 400;
        int y = std::rand() % 300;
        int m_x = 10 + std::rand() % 20;
        int m_y = 5 + std::rand() % 15;
        Label* lbl1 = new Label(Point(x, y), "Text", 100, 30);
        lbl1->set_font("LiberationSans-Regular.ttf");
        lbl1->is_hittest_visible = true;
        // lbl1->is_draggable = false;

        // style_btn(lbl1);
        s.add_control(lbl1);
    }

    for (int i = 0; i < 7; i++)
    {
        int x = std::rand() % 400;
        int y = std::rand() % 300;
        int m_x = 10 + std::rand() % 20;
        int m_y = 5 + std::rand() % 15;
        Button* lbl1 = new Button(Point(x, y), "Text", 100, 30, vmi);
        // lbl1->is_hittest_visible = true;
        // lbl1->is_draggable = true;

        style_btn(lbl1);
        s.add_control(lbl1);
    }
    s.run();
}

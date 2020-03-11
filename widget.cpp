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

void style_btn(Button*& btn)
{
    btn->set_border_color("E5D96E");
    btn->set_text_fill_normal("E5D96E");
    btn->set_normal_bg("6c6c6c");
    btn->set_hover_bg("7c7c7c");
    btn->set_focus_bg("7c7c7c");
    btn->set_drag_bg("8c8c8c");
    // btn->set_font("LiberationSans-Regular.ttf");
    btn->set_font("BoschSans-Medium.ttf");
}

void vmi()
{
    std::cout << "vmi\n";
}

int main(int argc, char const *argv[])
{
    Scene s(SCREEN_WIDTH, SCREEN_HEIGHT);
    for (int i = 0; i < 3; i++)
    {
        int x = std::rand() % 400;
        int y = std::rand() % 300;
        int m_x = 10 + std::rand() % 20;
        int m_y = 5 + std::rand() % 15;
        Spinner* lbl1 = new Spinner(Point(x, y), std::rand() % 100, 100, 30 + std::rand() % 20);
        lbl1->set_font("LiberationSans-Regular.ttf");
        // lbl1->set_font("BoschSans-Medium.ttf");
        lbl1->is_hittest_visible = true;
        lbl1->is_draggable = true;
        // lbl1->set_resizable(true);

        lbl1->max_value = 100;
        lbl1->min_value = 0;

        // style_btn(lbl1);
        s.add_control(lbl1);
    }

    // for (int i = 0; i < 3; i++)
    // {
    //     int x = std::rand() % 400;
    //     int y = std::rand() % 300;
    //     int m_x = 10 + std::rand() % 20;
    //     int m_y = 5 + std::rand() % 15;
    //     Label* lbl1 = new Label(Point(x, y), "Text", 100, 30);
    //     lbl1->set_font("BoschSans-Medium.ttf");
    //     // lbl1->set_font("LiberationSans-Regular.ttf");
    //     lbl1->is_hittest_visible = true;
    //     // lbl1->is_draggable = false;
    //     lbl1->set_resizable(true);

    //     lbl1->set_text("Not text!");
    //     // style_btn(lbl1);
    //     s.add_control(lbl1);
    // }

    for (int i = 0; i < 3; i++)
    {
        int x = std::rand() % 400;
        int y = std::rand() % 300;
        int m_x = 10 + std::rand() % 20;
        int m_y = 5 + std::rand() % 15;
        Label* lbl1 = new Label(Point(x, y), "Text", 100, 30);
        // lbl1->set_font("BoschSans-Medium.ttf");
        lbl1->set_font("LiberationSans-Regular.ttf");
        lbl1->is_hittest_visible = true;
        // lbl1->is_draggable = false;
        lbl1->set_resizable(true);

        // style_btn(lbl1);
        s.add_control(lbl1);
    }

    // for (int i = 0; i < 3; i++)
    // {
    //     int x = std::rand() % 400;
    //     int y = std::rand() % 300;
    //     int m_x = 10 + std::rand() % 20;
    //     int m_y = 5 + std::rand() % 15;
    //     Button* lbl1 = new Button(Point(x, y), "Text", 100, 30, vmi);
    //     // lbl1->is_hittest_visible = true;
    //     // lbl1->is_draggable = true;
    //     // lbl1->set_resizable(true);

    //     style_btn(lbl1);
    //     s.add_control(lbl1);
    // }
    s.run();
}

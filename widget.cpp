// #include "pch.hpp"
// #include "controls.hpp"
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
// #include "src/label.cpp"
#include "scene.hpp"
#include "src/spinner.cpp"

using namespace Controls;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void print_one()
{
    std::cout << "+1\n";
}

// void style_btn(Button*& btn)
// {
//     btn->set_border_color("E5D96E");
//     btn->set_text_fill_normal("E5D96E");
//     btn->set_normal_bg("6c6c6c");
//     btn->set_hover_bg("7c7c7c");
//     btn->set_focus_bg("7c7c7c");
//     btn->set_drag_bg("8c8c8c");
//     btn->set_font("LiberationSans-Regular.ttf");
//     // btn->set_font("BoschSans-Medium.ttf");
// }

void vmi()
{
    std::cout << "vmi\n";
}

// struct ExampleItem : public ComboBoxItem
// {
//     std::string name;
//     int value;

//     ExampleItem(std::string name, int value) : name(name), value(value) {}

//     std::string to_string() const override
//     {
//         return name + " [" + std::to_string(value) + "]";
//     }
// };

int main(int argc, char const *argv[])
{
    Scene s(SCREEN_WIDTH, SCREEN_HEIGHT);

    // std::vector<ComboBoxItem*> items = {
    //     new ExampleItem("Sample name", 1000),
    //     new ExampleItem("Example item", 2000),
    //     new ExampleItem("Something else", 9000),
    //     new ExampleItem("One more thing", 90),
    //     new ExampleItem("Yeah, you heard me", 10),
    //     new ExampleItem("what", 10)
    // };
    // ComboBox* combo = new ComboBox(vec2(20, 20), items, 200);
    // combo->set_font("LiberationSans-Regular.ttf");
    // s.add_control(combo);

    for (int i = 0; i < 3; i++)
    {
        int x = std::rand() % 400;
        int y = std::rand() % 300;
        int m_x = 10 + std::rand() % 20;
        int m_y = 5 + std::rand() % 15;
        Spinner* lbl1 = new Spinner(vec2(x, y), std::rand() % 100, 100, 50, vec2(7,7));
        lbl1->set_font("LiberationSans-Regular.ttf", 20);
        lbl1->is_hittest_visible = true;

        lbl1->max_value = 100;
        lbl1->min_value = 0;

        s.add_control(lbl1);
    }
    // for (int i = 0; i < 3; i++)
    // {
    //     int x = std::rand() % 400;
    //     int y = std::rand() % 300;
    //     int m_x = 10 + std::rand() % 20;
    //     int m_y = 5 + std::rand() % 15;
    //     TextBox* lbl1 = new TextBox(vec2(x, y), "TextBox", 100, 30, vec2(7,7));
    //     lbl1->set_font("LiberationSans-Regular.ttf");
    //     // lbl1->set_font("BoschSans-Medium.ttf");
    //     // lbl1->is_hittest_visible = true;
    //     lbl1->is_draggable = true;
    //     // lbl1->set_resizable(true);

    //     // style_btn(lbl1);
    //     s.add_control(lbl1);
    // }

    // for (int i = 0; i < 3; i++)
    // {
    //     int x = std::rand() % 400;
    //     int y = std::rand() % 300;
    //     int m_x = 10 + std::rand() % 20;
    //     int m_y = 5 + std::rand() % 15;
    //     Frame *f = new Frame(vec2(x, y), 100, 32);

    //     s.add_control(f);
    // }

    // for (int i = 0; i < 3; i++)
    // {
    //     int x = std::rand() % 400;
    //     int y = std::rand() % 300;
    //     int m_x = 10 + std::rand() % 20;
    //     int m_y = 5 + std::rand() % 15;
    //     Label* lbl1 = new Label(vec2(100, 100), "Label", 130, "LiberationSans-Regular.ttf", 25);
    //     // lbl1->set_font("BoschSans-Medium.ttf")
    //     // lbl1->set_font("LiberationSans-Regular.ttf");
    //     // lbl1->set_content_offset(vec2(7, 7));
    //     lbl1->is_hittest_visible = true;
    //     // lbl1->is_draggable = false;
    //     lbl1->set_resizable(true);

    //     // style_btn(lbl1);
    //     s.add_control(lbl1);
    // }

    // for (int i = 0; i < 3; i++)
    // {
    //     int x = std::rand() % 400;
    //     int y = std::rand() % 300;
    //     int m_x = 10 + std::rand() % 20;
    //     int m_y = 5 + std::rand() % 15;
    //     Button* lbl1 = new Button(vec2(x, y), "Text", vmi, 100, 35, vec2(30, 9));
    //     // lbl1->is_hittest_visible = true;
    //     // lbl1->is_draggable = true;
    //     // lbl1->set_resizable(true);

    //     style_btn(lbl1);
    //     s.add_control(lbl1);
    // }
    s.run();
}

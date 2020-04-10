#include "controls.hpp"
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include "listbox.hpp"

using namespace Controls;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const std::string FONT = "LiberationSans-Regular.ttf";

bool bg = true;
genv::color gray = genv::color(60, 60, 60);
genv::color pink = hex_to_color("ff9999");
void switch_background()
{
    if (bg = !bg)
    {
        Controls::BACKGROUND_COLOR = gray;
    }
    else
    {
        Controls::BACKGROUND_COLOR = pink;
    }
}

struct Entry : public ListBoxItem
{
    std::string name;
    int value;

    Entry(std::string name, int value) : name(name), value(value) {}

    std::string to_string() override
    {
        std::stringstream ss;
        ss << name << " [" << value << "]";
        return ss.str();
    }
};

void add_sample(Scene &s)
{
    // Frame
    Frame *f = new Frame(vec2(20, 20), 120, 70);
    f->set_border_thickness(3);
    f->set_resizable(true);
    s.add_control(f);

    // Label
    Label *l1 = new Label(vec2(150, 20), "Liberation Sans, 18px", 190, FONT, 18);
    l1->hittest_visible = true;
    l1->set_resizable(true);
    s.add_control(l1);

    Label *l2 = new Label(vec2(150, 60), "Default font Label", 190);
    l2->hittest_visible = true;
    l2->set_resizable(true);
    s.add_control(l2);

    // TextBox
    TextBox *tb1 = new TextBox(vec2(350, 20), "Liberation Sans, 20px", 220, FONT, 20);
    s.add_control(tb1);

    TextBox *tb2 = new TextBox(vec2(350,60), "Default font TextBox", 200);
    s.add_control(tb2);
 
    // Button
    Button *b1 = new Button(vec2(20, 100), switch_background, "Default button", 150, FONT, 16);
    s.add_control(b1);

    Button *b2 = new Button(vec2(20, 140), switch_background, "Styled button", 150, FONT, 16);
    b2->set_border_color("e5d96e");
    b2->set_text_fill_normal("e5d96e");
    b2->set_normal_bg("6c6c6c");
    b2->set_hover_bg("7c7c7c");
    b2->set_focus_bg("7c7c7c");
    b2->set_hold_bg("8c8c8c");
    s.add_control(b2);

    // Spinner
    Spinner *s1 = new Spinner(vec2(180, 100), 50, 80, FONT, 18);
    s1->set_border_thickness(2);
    s.add_control(s1);

    Spinner *s2 = new Spinner(vec2(180, 140), 1, 40, 40, vec2(7, 8), FONT, 18);
    s2->min_value = 1;
    s2->max_value = 9;
    s.add_control(s2);

    // ListBox
    ListBox *lb = new ListBox(vec2(180, 200), 120, 6, FONT, 16);
    lb->set_hover_bg("ffffff");
    lb->set_focus_bg("ffffff");
    lb->set_hold_bg("ffffff");
    lb->set_border_color("999999");
    s.add_control(lb);

    for (int i = 0; i < 70; i++)
    {
        lb->add_item(new Entry("entry", i));
    }
}

int main(int argc, char const *argv[])
{
    Scene s(SCREEN_WIDTH, SCREEN_HEIGHT);
    add_sample(s);
    s.run();
}

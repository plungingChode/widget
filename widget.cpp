#include "controls.hpp"
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>

using namespace Controls;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const std::string FONT = "LiberationSans-Regular.ttf";

bool bg = true;
genv::color gray = genv::color(60, 60, 60);
genv::color pink = hex_to_color(0xff9999);
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



ListBox *lb;
void remove_selected()
{
    lb->remove_item(lb->get_selected_index());
}

void add_entry()
{
    std::stringstream ss;
    for (int i = 0; i < 6; i++)
    {
        ss << char(std::rand()%(122-97)+97);
    }

    lb->add_item(new Entry(ss.str(), std::rand()%100));
}

bool by_value_desc(ListBoxItem *lhs, ListBoxItem *rhs)
{
    return static_cast<Entry*>(lhs)->value > static_cast<Entry*>(rhs)->value;
}
void sort_list_values()
{
    lb->sort(by_value_desc);
}

bool by_name_asc(ListBoxItem *lhs, ListBoxItem *rhs)
{
    return static_cast<Entry*>(lhs)->name < static_cast<Entry*>(rhs)->name;
}
void sort_list_names()
{
    lb->sort(by_name_asc);
}

ListBox *options;
class Option : public ListBoxItem
{
public:
    int id;
    std::string name;

    Option(int id, std::string name) : id(id), name(name) {}

    std::string to_string() override { return name; }
};

void dewit()
{
    Option* op = static_cast<Option*>(options->get_selected_item());
    if (op)
    {
        switch(op->id)
        {
        case 0: remove_selected(); break;
        case 1: add_entry(); break;
        case 2: sort_list_values(); break;
        case 3: sort_list_names(); break;
        default: break;
        }
    }
}

void add_sample(Scene &s)
{
    // Frame
    Frame *f = new Frame(&s, vec2(20, 20), 120, 70);
    f->set_border_thickness(3);
    f->set_resizable(true);
    
    // Label
    Label *l1 = new Label(&s, vec2(150, 20), "Liberation Sans, 18px", 190, FONT, 18);
    l1->hittest_visible = true;
    l1->set_resizable(true);
    
    Label *l2 = new Label(&s, vec2(150, 60), "Default font Label", 190);
    l2->hittest_visible = true;
    l2->set_resizable(true);
    
    // TextBox
    TextBox *tb1 = new TextBox(&s, vec2(350, 20), "Liberation Sans, 20px", 220, FONT, 20);
    TextBox *tb2 = new TextBox(&s, vec2(350,60), "Default font TextBox", 200);
     
    // Button
    Button *b1 = new Button(&s, vec2(20, 100), switch_background, "Default button", 150);
    Button *b2 = new Button(&s, vec2(20, 140), switch_background, "Styled button", 150, FONT, 16);
    b2->set_border_color(0xe5d96e);
    b2->set_text_fill_normal(0xe5d96e);
    b2->set_normal_bg(0x6c6c6c);
    b2->set_hover_bg(0x7c7c7c);
    b2->set_focus_bg(0x7c7c7c);
    b2->set_hold_bg(0x8c8c8c);
    
    // Spinner
    Spinner *s1 = new Spinner(&s, vec2(180, 100), 50, 80, FONT, 18);
    s1->set_border_thickness(2);
    
    Spinner *s2 = new Spinner(&s, vec2(180, 140), 1, 40, 40, vec2(7, 8), FONT, 18);
    s2->min_value = 1;
    s2->max_value = 9;
    
    // ListBox
    lb = new ListBox(&s, vec2(20, 200), 150, 6, FONT, 18);
    lb->set_border_color(0x999999);
    
    for (int i = 0; i < 10; i++)
    {
        lb->add_item(new Entry("entry", i));
    }

    Button *rm = new Button(&s, vec2(20, 330), remove_selected, "Remove selected", 150, vec2(10, 5), FONT);
    Button *add = new Button(&s, vec2(20, 360), add_entry, "Add random", 150, vec2(28, 5), FONT);
    Button *sbv = new Button(&s, vec2(20, 390), sort_list_values, "Sort by value", 150, vec2(25, 5), FONT);
    Button *sln = new Button(&s, vec2(20, 420), sort_list_names, "Sort by name", 150, vec2(25, 5), FONT);
    
    options = new ListBox(&s, vec2(180, 200), 200, 6, FONT, 18);
    options->set_border_color(0xff5555);
    
    options->add_item(new Option(0, "Remove selected"));
    options->add_item(new Option(1, "Add random"));
    options->add_item(new Option(2, "Sort by value (desc)"));
    options->add_item(new Option(3, "Sort by name"));

    Button *dw = new Button(&s, vec2(180, 330), dewit, "Do it", 200, vec2(80, 5), FONT);
}

class Sample
{
private:
    std::string word;

public:
    Sample(std::string word) : word(word) {}

    void f(const genv::event &ev)
    {
        if (ev.keycode == 'c')
        {
            printf("%s\n", word.c_str());
        }
    }
};

int main(int argc, char const *argv[])
{
    Scene s(SCREEN_WIDTH, SCREEN_HEIGHT);
    add_sample(s);

    Sample smp1("hello");
    s.add_listener(&Sample::f, &smp1);

    Sample smp2("goodbye");
    s.add_listener(&Sample::f, &smp2);
    
    return s.run();
}

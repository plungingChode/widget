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
const genv::font *FONT = new genv::font("LiberationSans-Regular.ttf", 16);

struct Entry : public ListBoxItem
{
    std::string name;
    int value;

    Entry(std::string name_, int value_) : name(name_), value(value_) {}

    std::string to_string() override
    {
        std::stringstream ss;
        ss << name << " [" << value << "]";
        return ss.str();
    }
};

class Option : public ListBoxItem
{
public:
    int id;
    std::string name;

    Option(int id_, std::string name_) : id(id_), name(name_) {}

    std::string to_string() override { return name; }
};

bool by_value_desc(ListBoxItem *lhs, ListBoxItem *rhs)
{
    return static_cast<Entry*>(lhs)->value > static_cast<Entry*>(rhs)->value;
}

bool by_name_asc(ListBoxItem *lhs, ListBoxItem *rhs)
{
    return static_cast<Entry*>(lhs)->name < static_cast<Entry*>(rhs)->name;
}

class SampleApp : public Scene
{
protected:
    enum action_t
    {
        switch_bg = 0,
        rm_selected,
        add_random,
        sort_vals,
        sort_names,
        exec_selected
    };

    Frame *f;
    Label *l1, *l2;
    TextBox *tb1, *tb2;
    Button *b1, *b2;
    Spinner *s1, *s2;
    ListBox *lb;
    Button *rm, *add, *srt1, *srt2;
    ListBox *options;
    Button *doit;

    bool bg = false;
    genv::color gray = genv::color(60, 60, 60);
    genv::color pink = hex_to_color(0xff9999);
    void switch_background()
    {
        if (bg)
        {
            Controls::BACKGROUND_COLOR = gray;
        }
        else
        {
            Controls::BACKGROUND_COLOR = pink;
        }
        bg = !bg;
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

    void sort_list_values() { lb->sort(by_value_desc); }
    void sort_list_names() { lb->sort(by_name_asc); }
    void remove_selected() { lb->remove_item(lb->get_selected_index()); }

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

public:
    SampleApp() : Scene(640, 480)
    {
        // Frame
        f = new Frame(this, 20,  20, 120, 70);
        f->set_border_thickness(3);
        f->set_resizable(true);
        
        // Label
        l1 = new Label(this, 150,  20, "Liberation Sans, 18px", 190, FONT);
        l1->hittest_visible = true;
        l1->set_resizable(true);
        
        l2 = new Label(this, 150,  60, "Default font Label", 190);
        l2->hittest_visible = true;
        l2->set_resizable(true);
        
        // TextBox
        tb1 = new TextBox(this, 350, 20, "Liberation Sans, 20px", 220, FONT);
        tb2 = new TextBox(this, 350, 60, "Default font TextBox", 200);

        // Button
        b1 = new Button(this, 20,  100, switch_bg, "Default button", 150);
        b2 = new Button(this, 20,  140, switch_bg, "Styled button", 150, FONT);
        b2->set_border_color(0xe5d96e);
        b2->set_text_fill_normal(0xe5d96e);
        b2->set_normal_bg(0x6c6c6c);
        b2->set_hover_bg(0x7c7c7c);
        b2->set_focus_bg(0x7c7c7c);
        b2->set_hold_bg(0x8c8c8c);
        
        // Spinner
        s1 = new Spinner(this, 180,  100, 50, 80, FONT);
        s1->set_border_thickness(2);
        
        s2 = new Spinner(this, 180,  140, 1, 40, 40, vec2(7, 8), FONT);
        s2->min_value = 1;
        s2->max_value = 9;
        
        // ListBox
        lb = new ListBox(this, 20,  200, 150, 6);
        lb->set_border_color(0x999999);
        
        for (int i = 0; i < 10; i++)
        {
            lb->add_item(new Entry("entry", i));
        }

        rm = new Button(this, 20, 330, rm_selected, "Remove selected", 150, vec2(10, 5), FONT);
        add = new Button(this, 20, 360, add_random, "Add random", 150, vec2(28, 5), FONT);
        srt1 = new Button(this, 20, 390, sort_vals, "Sort by value", 150, vec2(25, 5), FONT);
        srt2 = new Button(this, 20, 420, sort_names, "Sort by name", 150, vec2(25, 5), FONT);

        options = new ListBox(this, 180,  200, 200, 6, FONT);
        options->set_border_color(0xff5555);
        
        options->add_item(new Option(0, "Remove selected"));
        options->add_item(new Option(1, "Add random"));
        options->add_item(new Option(2, "Sort by value (desc)"));
        options->add_item(new Option(3, "Sort by name"));

        doit = new Button(this, 180,  330, exec_selected, "Do it", 200, vec2(80, 5), FONT);
    }

    void action(event ev) override
    {
        if (ev.type == ev_command)
        {
            switch(ev.command)
            {
            case rm_selected: remove_selected(); break;
            case add_random: add_entry(); break;
            case switch_bg: switch_background(); break;
            case sort_vals: sort_list_values(); break;
            case sort_names: sort_list_names(); break;
            case exec_selected: dewit(); break;
            default: break;
            }
        }

        if (ev.type == genv::ev_key && ev.keycode == genv::key_enter)
        {
            printf("hello\n");
        }
    }
};

int main(int argc, char const *argv[])
{
    SampleApp s;    
    // s.set_global_font(FONT);
    // Control::FORCE_GLOBAL_FONT = true;
    
    return s.run();
}

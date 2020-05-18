#include "controls.hpp"
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include "styles.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const genv::font *FONT = new genv::font("LiberationSans-Regular.ttf", 18);

struct Entry
{
    std::string name;
    int value;

    Entry(std::string name_, int value_) : name(name_), value(value_) {}

    std::string to_string() const
    {
        std::stringstream ss;
        ss << name << " [" << value << "]";
        return ss.str();
    }
};

class Option
{
public:
    int id;
    std::string name;

    Option(int id_, std::string name_) : id(id_), name(name_) {}

    std::string to_string() const { return name; }
};

bool by_value_desc(const Entry &lhs, const Entry &rhs)
{
    return lhs.value > rhs.value;
}

bool by_name_asc(const Entry &lhs, const Entry &rhs)
{
    return lhs.name < rhs.name;
}

class SampleApp : public Scene
{
protected:
    Frame *f;
    Label *l1, *l2;
    TextBox *tb1, *tb2;
    Button *b1, *b2;
    Spinner *s1, *s2;
    StaticText *st1, *st2;
    CheckBox *cb1, *cb2;
    ListBox *lb, *lb2;
    Button *rm, *add, *srt1, *srt2;
    Button *doit;

    std::vector<Entry> entries;
    std::vector<Option> options
    {
        Option(0, "Remove selected"),
        Option(1, "Add random"),
        Option(2, "Sort by value (desc)"),
        Option(3, "Sort by name")
    };

    bool bg = false;
    genv::color gray = genv::color(60, 60, 60);
    genv::color pink = hex_to_color(0xff9999);
    void switch_background()
    {
        if (bg)
        {
            background_color = gray;
        }
        else
        {
            background_color = pink;
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

        Entry e(ss.str(), std::rand()%100);

        entries.push_back(e);
        lb->add_item(e.to_string());
    }

    void sort_entries(std::function<bool(const Entry&, const Entry&)> sort)
    {
        std::sort(entries.begin(), entries.end(), sort);
        
        // synchronize with display
        std::vector<std::string> display;
        auto to_str = [](const Entry &e) { return e.to_string(); };
        std::transform(entries.begin(), entries.end(), std::back_inserter(display), to_str);
        lb->set_items(display);
    }

    void remove_selected() 
    { 
        int index = lb->get_selected_index();
        if (index != -1)
        {
            lb->remove_item(index); 
        }
    }

    void dewit()
    {
        int index = lb2->get_selected_index();
        if (index != -1)
        {
            switch(options[index].id)
            {
            case 0: remove_selected(); break;
            case 1: add_entry(); break;
            case 2: sort_entries(by_value_desc); break;
            case 3: sort_entries(by_name_asc); break;
            default: break;
            }
        }
    }

public:
    SampleApp() : Scene(640, 480)
    {
        // Frame
        f = new Frame(this, 20, 20, 120, 70);
        f->set_border_thickness(3);
        f->set_resizable(true);
        
        // Label
        l1 = new Label(this, 150, 20, 190, "Liberation Sans, 18px", FONT);
        l1->set_hittest_visible(true);
        l1->set_resizable(true);
        
        l2 = new Label(this, 150, 60, 190, "Default font Label");
        l2->set_hittest_visible(true);
        l2->set_resizable(true);
        
        // TextBox
        tb1 = new TextBox(this, 350, 20, "Liberation Sans, 18px", 220, FONT);
        set_style(tb1, DARK);
        tb2 = new TextBox(this, 350, 60, "Default font TextBox", 200);

        // Button
        b1 = new Button(this, 20,  100, 150, "Default button", [this](){ switch_background(); });
        b2 = new Button(this, 20,  140, 150, "Styled button",  [this](){ switch_background(); }, FONT);
        set_style(b2, DARK);
        
        // Spinner
        s1 = new Spinner(this, 180, 100, 80, 30, 0, INT_MIN, INT_MAX, FONT);
        s1->set_border_thickness(2);
        
        s2 = new Spinner(this, 180, 140, 40, 40, 1, -100, 100, FONT);
        s2->min_value = 1;
        s2->max_value = 9;
        set_style(s2, DARK);

        // StaticText
        // st1 = new StaticText(this, 300, 100, "Default font StaticText");
        st2 = new StaticText(this, 300, 140, "Liberation Sans, 18px", FONT);

        // CheckBox
        cb1 = new CheckBox(this, 300, 100, "Default font CheckBox");
        set_style(cb1, DARK);
        set_style(cb1, DEFAULT);
        
        // ListBox
        lb = new ListBox(this, 20,  200, 150, 6);
        // lb->set_border_color(0x999999);
        set_style(lb, DARK);
        
        for (int i = 0; i < 10; i++)
        {
            Entry e("entry", i+1);
            entries.push_back(e);
            lb->add_item(e.to_string());
        }

        rm = new Button(this, 20, 330, 150, "Remove selected", [this](){ remove_selected(); },  FONT);
        add = new Button(this, 20, 360, 150, "Add random", [this](){ add_entry(); }, FONT);
        srt1 = new Button(this, 20, 390, 150, "Sort by value", [this](){ sort_entries(by_value_desc); }, FONT);
        srt2 = new Button(this, 20, 420, 150, "Sort by name", [this](){ sort_entries(by_name_asc); }, FONT);

        lb2 = new ListBox(this, 180,  200, 200, 6, FONT);
        set_style(lb2, DEFAULT);
        // lb2->set_border_color(0xff5555);
        for (const Option &o : options)
        {
            lb2->add_item(o.to_string());
        }

        doit = new Button(this, 180,  330, 200, 50, "Do it", [this](){ dewit(); }, FONT);
    }
};

int main(int argc, char const *argv[])
{
    SampleApp s;    
    // s.set_global_font(FONT);
    // Control::FORCE_GLOBAL_FONT = true;
    
    return s.run();
}

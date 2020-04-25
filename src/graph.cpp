#include "graph.hpp"
#include <algorithm>
#include <sstream>
#include <map>

using namespace std;
using namespace genv;

namespace Controls
{
    Graph::Graph(Scene *s, int x_, int y_, int w_, int h_, vector<GraphItem*> items_, int items_vis, graph_t type_, const genv::font *f)
        : Frame(s, x_, y_, w_, h_, f), items(items_), items_visible(items_vis), type(type_)
    {
        border_thickness = 1;
    }

    Graph::Graph(Scene *s, int x_, int y_, int w_, int h_, int items_vis, graph_t type_, const genv::font *f)
        : Graph(s, x_, y_, w_, h_, {}, items_vis, type_, f)
    {
    }

    void Graph::add_item(GraphItem *item)
    {
        items.push_back(item);
        schedule_update();
    }

    void Graph::remove_item(int index)
    {
        items.erase(items.begin() + index);
        schedule_update();
    }

    void Graph::sort(graph_sort comp)
    {
        std::sort(items.begin(), items.end(), comp);
        schedule_update();
    }

    void Graph::set_font(const genv::font *f)
    {
        
    }

    void Graph::update()
    {
        Frame::update();

        // find boundaries
        auto minmax_comp = [](const GraphItem *g1, const GraphItem *g2)
        {
            return g1->x() < g2->x();
        };
        auto bounds = minmax_element(items.begin(), items.end(), minmax_comp);
        int min_x = (*bounds.first)->x();
        int max_x = (*bounds.second)->x();

        min_x = min(min_x, 0);
        max_x = max(max_x, 0);

        // create labels, find x inset
        map<string, int> x_labels;
        int line_height = font ? font->font_size+2 : 18;
        int x_inset = 0;
        int y_inset = 5+line_height;
        int ticks = (h-y_inset) / line_height;
        int step = (max_x-min_x) / ticks;
        while (min_x + (ticks-1)*step < max_x)
        {
            ++step;
        }
        for (int i = 0; i < ticks; i++)
        {
            string lbl = to_string(min_x + i*step);
            int lbl_width = rendered.twidth(lbl);
            if (lbl_width > x_inset)
            {
                x_inset = lbl_width;
            }
            x_labels[lbl] = lbl_width;
        }

        x_inset += 8;
        rendered
            << border << move_to(x_inset, 5) 
            << line(0, h-y_inset) << line(w-x_inset-5, 0);

        int cnt = 0;
        int y_base = h-y_inset-line_height;
        int y_offset = font ? 0 : rendered.cascent();
        for (auto it = x_labels.begin(); it != x_labels.end(); ++it)
        {
            auto p = *it;
            rendered
                << move_to(x_inset-3-p.second, y_base+y_offset-cnt*line_height) 
                << text(p.first);
            ++cnt;
        }

        // printf("ticks=%d\n", ticks);
        // printf("line_height=%d\n", line_height);
        // printf("y_inset=%d\n", y_inset);
        // printf("max_x=%d\n", max_x);
        // printf("inset=%d\n", x_inset);
        // printf("first=%s, last=%s\n", x_labels.begin()->first.c_str(), x_labels.rbegin()->first.c_str());
    }
}


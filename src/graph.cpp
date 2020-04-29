#include "graph.hpp"
#include <algorithm>

namespace Controls
{
    Graph::Graph(Scene *s, int x_, int y_, int w_, int h_, std::vector<GraphItem*> items_, int items_vis, graph_t type_, const genv::font *f)
        : Frame(s, x_, y_, w_, h_, f), items(items_), items_visible(items_vis), type(type_)
    {
        
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

    }
}


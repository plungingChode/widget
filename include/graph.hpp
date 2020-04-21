#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include "frame.hpp"
#include <vector>
#include <functional>
#include <climits>

namespace Controls
{
    class GraphItem
    {
        virtual int x() = 0;
        virtual const std::string& y() const = 0;
    };

    enum graph_t
    {
        graph_bar = 0,
        graph_line,
        graph_marker,
        graph_line_marker
    };

    typedef std::function<bool(GraphItem*, GraphItem*)> graph_sort;

    class Graph : public Frame
    {
    protected:
        std::vector<GraphItem*> items;
        int items_visible;

        rect draw_area;

        graph_t type;

        virtual void update() override;

    public:
        Graph(Scene *owner, int x, int y, int width, int height, std::vector<GraphItem*> items, int items_visible = INT_MAX, graph_t type = graph_bar, const genv::font *font = nullptr);
        Graph(Scene *owner, int x, int y, int width, int height, int items_visible = INT_MAX, graph_t type = graph_bar, const genv::font *font = nullptr);

        void add_item(GraphItem *item);
        void remove_item(int index);
        void sort(graph_sort comp);

        virtual void set_font(const genv::font *f);

        virtual void on_mouse_ev(const genv::event &mouse_ev, bool btn_held) override { }
        virtual void on_key_ev(const genv::event &key_ev, int key_held) override { }
    };
}

#endif
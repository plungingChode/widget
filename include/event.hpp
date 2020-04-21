#ifndef EVENT_HPP_INCLUDED
#define EVENT_HPP_INCLUDED

#include "graphics.hpp"

namespace Controls
{
    struct event : public genv::event
    {
        int command;
    };

    enum event_t
    {
        ev_command = -1
    };
}

#endif
#ifndef HEADER_GUARD_EVENT_H
#define HEADER_GUARD_EVENT_H

#include <SDL2/SDL_events.h>

namespace sdl {
using event = SDL_Event;

static int poll_event(event* event) noexcept {
    return SDL_PollEvent(event);
}

static int get_event(event* event) noexcept {
    return SDL_PeepEvents(event, 1, SDL_GETEVENT,
                          SDL_FIRSTEVENT, SDL_LASTEVENT);
}

static void pump_events() noexcept { SDL_PumpEvents(); }
}

#endif

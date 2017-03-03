#ifndef HEADER_GUARD_RECT_H
#define HEADER_GUARD_RECT_H

#include <SDL2/SDL_rect.h>

namespace sdl {
using rect = SDL_Rect;

static rect rect_of(int x, int y, int w, int h) noexcept {
    rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    return r;
}
}

#endif

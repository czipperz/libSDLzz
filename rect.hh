/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2017 Chris Gregory czipperz@gmail.com
 */

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

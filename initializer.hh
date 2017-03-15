/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2017 Chris Gregory czipperz@gmail.com
 */

#ifndef HEADER_GUARD_INITIALIZER_H
#define HEADER_GUARD_INITIALIZER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "error.hh"

namespace sdl {
struct initializer {
    initializer() {
        if (SDL_Init(SDL_INIT_VIDEO)) {
            throw error();
        }
    }
    ~initializer() noexcept { SDL_Quit(); }
};

namespace img {
struct initializer {
    initializer() {
        if (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) {
            throw error();
        }
    }
    ~initializer() noexcept { IMG_Quit(); }
};
}
}

#endif

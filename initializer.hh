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

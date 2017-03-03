#ifndef HEADER_GUARD_ERROR_H
#define HEADER_GUARD_ERROR_H

#include <stdexcept>

extern "C" {
const char* SDL_GetError();
}

namespace sdl {
struct error : std::runtime_error {
    error() : std::runtime_error(SDL_GetError()) {}
};

static void throw_if(bool x) {
    if (x) {
        throw error();
    }
}
}

#endif

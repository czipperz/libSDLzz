/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2017 Chris Gregory czipperz@gmail.com
 */

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

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2017 Chris Gregory czipperz@gmail.com
 */

#ifndef HEADER_GUARD_PIXEL_FORMAT_H
#define HEADER_GUARD_PIXEL_FORMAT_H

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_blendmode.h>

namespace sdl {
using pixel_format = SDL_PixelFormat;
using blend_mode = SDL_BlendMode;
}

#endif

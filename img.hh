#ifndef HEADER_GUARD_IMG_H
#define HEADER_GUARD_IMG_H

#include <SDL2/SDL_image.h>

#include "surface.hh"
#include "texture.hh"
#include "renderer.hh"

namespace sdl {
namespace img {
static sdl::surface load(const char* path) {
    return sdl::surface(IMG_Load(path));
}

static sdl::texture
load_texture(sdl::renderer& renderer, const char* path) {
    return sdl::texture(IMG_LoadTexture(renderer.get(), path));
}
}
}

#endif

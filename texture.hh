/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2017 Chris Gregory czipperz@gmail.com
 */

#ifndef HEADER_GUARD_TEXTURE_H
#define HEADER_GUARD_TEXTURE_H

#include <SDL2/SDL_render.h>
#include "surface.hh"
#include "error.hh"
#include "rect.hh"

namespace sdl {
class renderer;

class texture {
    SDL_Texture* _texture;

public:
    inline texture(sdl::renderer& renderer, Uint32 format, int access,
                   int w, int h);
    inline texture(sdl::renderer& renderer, const sdl::surface&);
    explicit texture(SDL_Texture* texture)
        : _texture(texture) {
        if (!texture) {
            throw sdl::error();
        }
    }
    ~texture() noexcept { SDL_DestroyTexture(_texture); }

    texture(texture&& other) noexcept : _texture(0) { swap(other); }
    texture& operator=(texture&& other) noexcept {
        swap(other);
        return *this;
    }

    SDL_Texture* get() noexcept { return _texture; }
    SDL_Texture* get_unsafe() const noexcept { return _texture; }

    void swap(texture& other) { std::swap(_texture, other._texture); }

    class lock {
        SDL_Texture* _texture;

    public:
        void* pixels;
        int pitch;

        lock(sdl::texture& texture, const rect* rect = nullptr)
            : lock(texture.get(), rect) {}
        lock(sdl::texture& texture, const rect& rect)
            : lock(texture, &rect) {}
        lock(SDL_Texture* texture, const rect* rect = nullptr)
            : _texture(texture) {
            throw_if(
                !SDL_LockTexture(_texture, rect, &pixels, &pitch));
        }
        ~lock() noexcept {
            SDL_UnlockTexture(_texture);
        }

        lock(const lock&) = delete;
        lock(lock&&) = delete;
        lock& operator=(const lock&) = delete;
        lock& operator=(lock&&) = delete;
    };
};
}

#include "renderer.hh"

namespace sdl {
texture::texture(sdl::renderer& renderer, Uint32 format, int access,
                 int w, int h)
    : texture(
          SDL_CreateTexture(renderer.get(), format, access, w, h)) {}

texture::texture(sdl::renderer& renderer, const sdl::surface& surface)
    : texture(SDL_CreateTextureFromSurface(renderer.get(),
                                           surface.get_unsafe())) {}
}

#endif

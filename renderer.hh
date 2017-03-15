/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2017 Chris Gregory czipperz@gmail.com
 */

#ifndef HEADER_GUARD_RENDERER_H
#define HEADER_GUARD_RENDERER_H

#include "window.hh"
#include "error.hh"
#include "rect.hh"

namespace sdl {
class texture;
class renderer {
    SDL_Renderer* _renderer;

public:
    renderer(window& window, int index, Uint32 flags)
        : renderer(SDL_CreateRenderer(window.get(), index, flags)) {}
    explicit renderer(SDL_Renderer* renderer)
        : _renderer(renderer) {
        throw_if(!renderer);
    }
    ~renderer() noexcept { SDL_DestroyRenderer(_renderer); }

    renderer(renderer&& other) noexcept : _renderer(0) {
        swap(other);
    }
    renderer& operator=(renderer&& other) noexcept {
        swap(other);
        return *this;
    }

    SDL_Renderer* get() noexcept { return _renderer; }
    SDL_Renderer* get_unsafe() const noexcept { return _renderer; }

    void swap(renderer& other) {
        std::swap(_renderer, other._renderer);
    }

    void set_draw_blend_mode(SDL_BlendMode blendMode) {
        throw_if(SDL_SetRenderDrawBlendMode(_renderer, blendMode));
    }
    void set_draw_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) {
        throw_if(SDL_SetRenderDrawColor(_renderer, r, g, b, a));
    }

    void present() noexcept { SDL_RenderPresent(_renderer); }

    void clear() { throw_if(SDL_RenderClear(_renderer)); }
    void fill_rect(const rect* rect) {
        throw_if(SDL_RenderFillRect(_renderer, rect));
    }
    void fill_rect(const rect& rect) { fill_rect(&rect); }
    void fill() { fill_rect(nullptr); }

    inline void copy(const texture&, const rect* src = nullptr,
                     const rect* dest = nullptr);
    void
    copy(const texture& texture, const rect& src, const rect& dest) {
        copy(texture, &src, &dest);
    }

    inline void set_target(texture&);
    void unset_target() {
        throw_if(SDL_SetRenderTarget(_renderer, nullptr));
    }
};
}

#include "texture.hh"

namespace sdl {
void renderer::copy(const texture& texture, const rect* src,
                    const rect* dest) {
    throw_if(
        SDL_RenderCopy(_renderer, texture.get_unsafe(), src, dest));
}
void renderer::set_target(texture& texture) {
    throw_if(SDL_SetRenderTarget(_renderer, texture.get()));
}
}

#endif

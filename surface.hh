#ifndef HEADER_GUARD_SURFACE_H
#define HEADER_GUARD_SURFACE_H

#include <SDL2/SDL_surface.h>

#include "error.hh"
#include "rect.hh"
#include "types.hh"

namespace sdl {
class surface {
    SDL_Surface* _surface;

public:
    surface(const surface& source, const sdl::pixel_format& fmt,
            Uint32 flags)
        : surface(
              SDL_ConvertSurface(source.get_unsafe(), &fmt, flags)) {}
    surface(int width, int height, int depth,
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
            Uint32 Rmask = 0xff000000, Uint32 Gmask = 0x00ff0000,
            Uint32 Bmask = 0x0000ff00, Uint32 Amask = 0x000000ff
#else
            Uint32 Rmask = 0x000000ff, Uint32 Gmask = 0x0000ff00,
            Uint32 Bmask = 0x00ff0000, Uint32 Amask = 0xff000000
#endif
            )
        : surface(SDL_CreateRGBSurface(0, width, height, depth,
                                       Rmask, Gmask, Bmask, Amask)) {}
    surface(void* pixels, int width, int height, int depth, int pitch,
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
            Uint32 Rmask = 0xff000000, Uint32 Gmask = 0x00ff0000,
            Uint32 Bmask = 0x0000ff00, Uint32 Amask = 0x000000ff
#else
            Uint32 Rmask = 0x000000ff, Uint32 Gmask = 0x0000ff00,
            Uint32 Bmask = 0x00ff0000, Uint32 Amask = 0xff000000
#endif
            )
        : surface(SDL_CreateRGBSurfaceFrom(pixels, width, height,
                                           depth, pitch, Rmask, Gmask,
                                           Bmask, Amask)) {}
    explicit surface(SDL_Surface* surface)
        : _surface(surface) {
        throw_if(!surface);
    }
    ~surface() noexcept { SDL_FreeSurface(_surface); }

    surface(surface&& other) noexcept : _surface(nullptr) {
        swap(other);
    }
    surface& operator=(surface&& other) noexcept {
        swap(other);
        return *this;
    }

    SDL_Surface* get() noexcept { return _surface; }
    const SDL_Surface* get() const noexcept { return _surface; }
    SDL_Surface* get_unsafe() const noexcept { return _surface; }

    void swap(surface& other) noexcept {
        std::swap(_surface, other._surface);
    }

    void fill_rect(const rect& rect, Uint32 color) {
        fill_rect(&rect, color);
    }
    void fill_rect(const rect* rect, Uint32 color) {
        throw_if(SDL_FillRect(_surface, rect, color));
    }

    void fill(Uint32 color) { fill_rect(nullptr, color); }

    void fill_rects(const rect* rects, int num_rects, Uint32 color) {
        throw_if(SDL_FillRects(_surface, rects, num_rects, color));
    }

    rect get_clip_rect() noexcept {
        rect rect;
        get_clip_rect(rect);
        return rect;
    }
    void get_clip_rect(rect& rect) noexcept {
        SDL_GetClipRect(_surface, &rect);
    }

    Uint32 get_color_key() {
        Uint32 key;
        throw_if(SDL_GetColorKey(_surface, &key));
        return key;
    }

    Uint8 get_alpha_mod() noexcept {
        Uint8 alpha;
        SDL_GetSurfaceAlphaMod(_surface, &alpha);
        return alpha;
    }

    blend_mode get_blend_mode() {
        blend_mode blend_mode;
        get_blend_mode(blend_mode);
        return blend_mode;
    }
    void get_blend_mode(blend_mode& blend_mode) {
        throw_if(SDL_GetSurfaceBlendMode(_surface, &blend_mode));
    }

    void get_color_mod(Uint8* r, Uint8* g, Uint8* b) const noexcept {
        SDL_GetSurfaceColorMod(_surface, r, g, b);
    }
    Uint8 get_red_mod() const noexcept {
        Uint8 r;
        get_color_mod(&r, 0, 0);
        return r;
    }
    Uint8 get_green_mod() const noexcept {
        Uint8 g;
        get_color_mod(0, &g, 0);
        return g;
    }
    Uint8 get_blue_mod() const noexcept {
        Uint8 b;
        get_color_mod(0, 0, &b);
        return b;
    }

    bool must_lock() const noexcept {
        return SDL_MUSTLOCK(_surface);
    }

    class lock {
        SDL_Surface* _surface;

    public:
        lock(surface& s) : lock(s.get()) {}
        lock(SDL_Surface* surface) : _surface(surface) {
            SDL_LockSurface(_surface);
        }
        ~lock() { SDL_UnlockSurface(_surface); }
    };
};
}

#endif

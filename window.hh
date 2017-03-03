#ifndef HEADER_GUARD_WINDOW_H
#define HEADER_GUARD_WINDOW_H

#include <SDL2/SDL.h>
#include <utility>
#include "error.hh"

namespace sdl {
class renderer;

class window {
    SDL_Window* _window;

public:
    window(const char* title, int x, int y, int w, int h,
           Uint32 flags)
        : window(SDL_CreateWindow(title, x, y, w, h, flags)) {}
    explicit window(SDL_Window* window)
        : _window(window) {
        throw_if(!window);
    }
    ~window() noexcept { SDL_DestroyWindow(_window); }

    window(window&& other) noexcept : _window(0) { swap(other); }
    window& operator=(window&& other) noexcept {
        swap(other);
        return *this;
    }

    SDL_Window* get() noexcept { return _window; }

    void swap(window& other) { std::swap(_window, other._window); }

    int width() const noexcept {
        int w;
        SDL_GetWindowSize(_window, &w, nullptr);
        return w;
    }
    int height() const noexcept {
        int h;
        SDL_GetWindowSize(_window, nullptr, &h);
        return h;
    }
};
}

#endif

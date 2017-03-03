# libSDLzz

This is a header only wrapper for libSDL2.

All of the classes reside in the "sdl" namespace.  A get method is
defined to get the native object.  Exceptions are used instead of
error codes.  All the classes accept a native object to take ownership
if you want to do a manual initialization.

Example:

    sdl::initializer sdl;
    sdl::window window("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       600, 600, SDL_WINDOW_SHOWN);
    sdl::renderer renderer(window, -1, 0);
    // Load image from file into GPU
    sdl::texture picture = sdl::img::load_texture(renderer, "PATH");
    // Main loop
    bool done = false;
    while (!done) {
        // Handle key events
        sdl::event event;
        while (sdl::poll_event(&event)) {
        case SDL_QUIT:
            done = true;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_q) {
                done = true;
            }
            break;
        }

        // Render
        renderer.copy(picture);
        renderer.present();
    }

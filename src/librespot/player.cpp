#include "player.hpp"
#include <dlfcn.h>
#include <iostream>

Librespot::Librespot(const std::string &lib_path) {
    handle = dlopen(lib_path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Failed to load librespot library: " << dlerror() << std::endl;
        return;
    }

    play_track_func = (PlayTrackFunc) dlsym(handle, "spotify_play");
    if (!play_track_func) {
        std::cerr << "Failed to load spotify_play function: " dlerror() << std::endl;
    }
}

Librespot::~Librespot() {
    if (handle) {
        dlclose(handle);
    }
}

void Librespot::play_track(const std::string &track_id) {
    if (play_track_func) {
        play_track_func(track_id.c_str());
    } else {
        std::cerr << "spotify_play function not loaded." << std::endl;
    }
}

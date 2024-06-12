//  SuperTuxBattleMelee
//  Copyright (C) 2024 Taliesin Perscilla "FlutterTal" Ambroise
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "main_loop.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>

MainLoop MainLoop::singleton;

MainLoop::MainLoop() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL! (%s)", SDL_GetError());
        throw std::runtime_error("SDL error");
    }

    if(!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) & (IMG_INIT_JPG | IMG_INIT_PNG))) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL_image! (%s)\n", IMG_GetError());
        SDL_Quit();
        throw std::runtime_error("IMG error");
    }

    if(TTF_Init() < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL_ttf! (%s)\n", TTF_GetError());
        IMG_Quit();
        SDL_Quit();
        throw std::runtime_error("TTF error");
    }

    window = new Window();
}

MainLoop::~MainLoop() {
    delete window;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

MainLoop * MainLoop::get_singleton() {
    return &MainLoop::singleton;
}

void MainLoop::run() {
    while(!window->should_close()) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
            case SDL_QUIT:
                window->close_window();
                break;
            }
        }

        window->swap_window();
    }
}
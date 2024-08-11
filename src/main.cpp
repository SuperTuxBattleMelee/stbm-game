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

#include "video/window.h"
#include "video/gl/glcontext21.h"
#include <stdlib.h>
#ifdef __GNUC__
#include <unistd.h>
#endif
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

int main(int argc, char * argv[]) {
#ifdef __GNUC__
    if(geteuid() == 0) {
        fprintf(stderr, "Executing the game as root user is forbidden for security purpose\n");
        return EXIT_FAILURE;
    }
#endif
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL! (%s)", SDL_GetError());
        return EXIT_FAILURE;
    }

    if(!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) & (IMG_INIT_JPG | IMG_INIT_PNG))) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL_image! (%s)", IMG_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    if(TTF_Init() < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL_ttf! (%s)", TTF_GetError());
        IMG_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // TODO: Thinking about using the other SDL libraries

    {
        Window window;
        GLContext * context = new GLContext21();
        while(!window.should_close()) {
            // TODO: Create an Event class to not bloat this part later on
            SDL_Event event;
            while(SDL_PollEvent(&event)) {
                switch(event.type) {
                case SDL_QUIT:
                    window.close_window();
                    break;
                }
            }

            int w, h;
            SDL_GetWindowSize(window.get_window(), &w, &h);
            context->bind();
            context->blend_func(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            context->ortho(w, h);
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            window.swap_window();
        }

        delete context;
    }
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}

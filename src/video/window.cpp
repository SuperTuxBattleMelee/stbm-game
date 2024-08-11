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
#include <stdexcept>

Window::Window() {
#if defined(OPENGL_21)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
#elif defined(OPENGL_33)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
#endif
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_DisplayMode mode;
    if(SDL_GetDesktopDisplayMode(0, &mode) != 0)
        throw std::runtime_error("Couldn't get desktop display mode");
    
    window = SDL_CreateWindow("SuperTuxBattleMelee", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mode.w, mode.h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if(window == nullptr)
        throw std::runtime_error("Couldn't create the window");
    
    context = SDL_GL_CreateContext(window);
    if(context == nullptr)
        throw std::runtime_error("Couldn't create the context");
}

Window::~Window() {
    if(context)
        SDL_GL_DeleteContext(context);
    
    if(window)
        SDL_DestroyWindow(window);
}

void Window::swap_window() {
    SDL_GL_SwapWindow(window);
}
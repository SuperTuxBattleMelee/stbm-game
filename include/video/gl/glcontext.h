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

#ifndef GLCONTEXT_H
#define GLCONTEXT_H

#include "gl.h"

class GLContext {
public:
    virtual ~GLContext() {}

    virtual void bind() = 0;
    virtual void ortho(double w, double h) = 0;
    virtual void blend_func(GLenum src, GLenum dst) = 0;
};

#endif
#!/usr/bin/env python

EnsureSConsVersion(3, 0, 0)
EnsurePythonVersion(3, 6)

env = Environment(LIBS=['GL', 'SDL2', 'SDL2_image', 'SDL2_ttf'], CXXCOMSTR='Compiling $TARGET', LINKCOMSTR='Linking $TARGET')

Export('env')

SConscript('src/SCsub')

program = env.Program('bin/SuperTuxBattleMelee', env.game_files)
env.NoCache(program)
env.Precious(program)
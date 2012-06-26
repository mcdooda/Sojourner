#ifndef TIME_H
 #define TIME_H

#include <lua5.1/lua.h>

int luaopen_time(lua_State* L);

int time_total            (lua_State* L);
int time_elapsed          (lua_State* L);
int time_beginFrame       (lua_State* L);
int time_endFrame         (lua_State* L);
int time_beginUpdate      (lua_State* L);
int time_endUpdate        (lua_State* L);
int time_setFrameRate     (lua_State* L);
int time_frameRate        (lua_State* L);
int time_realFrameRate    (lua_State* L);
int time_frameDuration    (lua_State* L);
int time_setFrameDuration (lua_State* L);

float get_time();
void sleeps(float duration);

#endif

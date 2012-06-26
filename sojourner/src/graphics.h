#ifndef GRAPHICS_H
 #define GRAPHICS_H

#include <lua5.1/lua.h>

int luaopen_graphics(lua_State* L);

int graphics_open              (lua_State* L);
int graphics_close             (lua_State* L);
int graphics_desktopResolution (lua_State* L);
int graphics_beginFrame        (lua_State* L);
int graphics_endFrame          (lua_State* L);
int graphics_clearColor        (lua_State* L);

#endif

#ifndef DEPS_NEWCLASS_H
 #define DEPS_NEWCLASS_H

#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>

void class(lua_State* L, const char* name, const char* superclasses[], lua_CFunction allocator, const luaL_Reg methods[]);

#endif

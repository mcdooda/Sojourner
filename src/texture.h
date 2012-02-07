#ifndef TEXTURE_H
 #define TEXTURE_H

#include <lua5.1/lua.h>
#include <GL/gl.h>

typedef struct
{
  char* filename;
  GLuint id;
  int width;
  int height;
} Texture;

int luaopen_texture(lua_State* L);

int texture_allocator  (lua_State* L);
int texture_initialize (lua_State* L);
int texture_destroy    (lua_State* L);
int texture_name       (lua_State* L);
int texture_smooth     (lua_State* L);
int texture_size       (lua_State* L);
int texture_draw       (lua_State* L);

#endif

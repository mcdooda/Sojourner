#ifndef SPRITE_H
 #define SPRITE_H

#include <lua5.1/lua.h>
#include "texture.h"
#include "deps/rectangle.h"

typedef struct {
  Texture* texture;
  float x;
  float y;
  float center_x;
  float center_y;
  float scale_x;
  float scale_y;
  float rotation;
  Rectangle source;
  Rectangle destination;
} Sprite;

int luaopen_sprite(lua_State* L);

int sprite_allocator      (lua_State* L);
int sprite_initialize     (lua_State* L);
int sprite_destroy        (lua_State* L);
int sprite_clone          (lua_State* L);
int sprite_texture        (lua_State* L);
int sprite_setDestination (lua_State* L);
int sprite_position       (lua_State* L);
int sprite_setSource      (lua_State* L);
int sprite_setCenter      (lua_State* L);
int sprite_setScale       (lua_State* L);
int sprite_setRotation    (lua_State* L);
int sprite_draw           (lua_State* L);

#endif

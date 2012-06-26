#include <lua5.1/lauxlib.h>
#include "sprite.h"
#include "deps/newclass.h"

int luaopen_sprite(lua_State* L)
{
  const char* superclasses[] = {
    NULL
  };
  const luaL_Reg methods[] = {
    {"initialize",     sprite_initialize},
    {"destroy",        sprite_destroy},
    {"clone",          sprite_clone},
    {"texture",        sprite_texture},
    {"position",       sprite_position},
    {"setDestination", sprite_setDestination},
    {"setSource",      sprite_setSource},
    {"setCenter",      sprite_setCenter},
    {"setScale",       sprite_setScale},
    {"setRotation",    sprite_setRotation},
    {"draw",           sprite_draw},
    {NULL, NULL}
  };
	class(L, "Sprite", superclasses, sprite_allocator, methods);
	return 0;
}

int sprite_allocator(lua_State* L)
{
  /*
  1: metatable
  */
  lua_newuserdata(L, sizeof(Sprite)); /* 2: userdata */
  lua_pushvalue(L, -2);               /* 3: metatable */
  lua_setmetatable(L, -2);            /* 2: userdata */
  return 1;
}

int sprite_initialize(lua_State* L)
{
  /*
  1: sprite
  2: texture
  */
  Sprite* sprite = lua_touserdata(L, 1);
  Texture* texture = lua_touserdata(L, 2);
  
  sprite->texture = texture;
  sprite->x = 0;
  sprite->y = 0;
  sprite->center_x = 0;
  sprite->center_y = 0;
  sprite->scale_x = 1;
  sprite->scale_y = 1;
  sprite->rotation = 0;
  
  rectangle_set(&sprite->destination, 0, 0, texture->width, texture->height);
  rectangle_set(&sprite->source, 0, 1, 1, -1);
  
  return 0;
}

int sprite_destroy(lua_State* L)
{
  /*
  1: sprite
  */
  /* nothing */
  return 0;
}

int sprite_clone(lua_State* L)
{
  /*
  1: sprite
  */
  Sprite* sprite = lua_touserdata(L, 1);
  lua_newuserdata(L, sizeof(Sprite)); /* 2: clone */
  *(Sprite*)lua_touserdata(L, -1) = *sprite;
  lua_getmetatable(L, -2); /* 3: metatable */
  lua_setmetatable(L, -2); /* 2: clone */
  return 1;
}

int sprite_texture(lua_State* L)
{
  /*
  1: sprite
  */
  Sprite* sprite = lua_touserdata(L, 1);
  lua_pushlightuserdata(L, sprite->texture);
  return 1;
}

int sprite_position(lua_State* L)
{
  /*
  1: sprite
  */
  Sprite* sprite = lua_touserdata(L, 1);
  lua_pushnumber(L, sprite->x - sprite->center_x);
  lua_pushnumber(L, sprite->y - sprite->center_y);
  return 2;
}

int sprite_setDestination(lua_State* L)
{
  /*
  1: sprite
  2: x
  3: y
  4: (opt) width
  5: (opt) height
  */
  Sprite* sprite = lua_touserdata(L, 1);
  sprite->x = luaL_checknumber(L, 2);
  sprite->y = luaL_checknumber(L, 3);
  float width = luaL_optnumber(L, 4, rectangle_width(&sprite->destination));
  float height = luaL_optnumber(L, 5, rectangle_height(&sprite->destination));
  rectangle_set(&sprite->destination, -sprite->center_x, -sprite->center_y, width, height);
  return 0;
}

int sprite_setSource(lua_State* L)
{
  /*
  1: sprite
  2: left
  3: right
  4: top
  5: bottom
  */
  Sprite* sprite = lua_touserdata(L, 1);
  float left = luaL_checknumber(L, 2);
  float right = luaL_checknumber(L, 3);
  float top = luaL_checknumber(L, 4);
  float bottom = luaL_checknumber(L, 5);
  rectangle_set(&sprite->source, left, -top, right - left, top - bottom);
  return 0;
}

int sprite_setCenter(lua_State* L)
{
  /*
  1: sprite
  2: center x
  3: center y
  */
  Sprite* sprite = lua_touserdata(L, 1);
  sprite->center_x = luaL_checknumber(L, 2);
  sprite->center_y = luaL_checknumber(L, 3);
  rectangle_setX(&sprite->destination, -sprite->center_x);
  rectangle_setY(&sprite->destination, -sprite->center_y);
  return 0;
}

int sprite_setScale(lua_State* L)
{
  /*
  1: sprite
  2: scale x
  3: scale y
  */
  Sprite* sprite = lua_touserdata(L, 1);
  sprite->scale_x = luaL_checknumber(L, 2);
  sprite->scale_y = luaL_checknumber(L, 3);
  return 0;
}

int sprite_setRotation(lua_State* L)
{
  /*
  1: sprite
  2: rotation
  */
  Sprite* sprite = lua_touserdata(L, 1);
  sprite->rotation = luaL_checknumber(L, 2);
  return 0;
}

int sprite_draw(lua_State* L)
{
  /*
  1: sprite
  */
  Sprite* sprite = lua_touserdata(L, 1);
  
  glBindTexture(GL_TEXTURE_2D, sprite->texture->id);
  
  glPushMatrix();
    glTranslatef(sprite->x, sprite->y, 0);
    glRotatef(sprite->rotation, 0, 0, 1);
    glScalef(sprite->scale_x, sprite->scale_y, 1);
    glVertexPointer(2, GL_FLOAT, 0, &sprite->destination);
    glTexCoordPointer(2, GL_FLOAT, 0, &sprite->source);
    glDrawArrays(GL_QUADS, 0, 4);
  glPopMatrix();
  
  return 0;
}



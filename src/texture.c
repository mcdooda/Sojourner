#include <stdlib.h>
#include <string.h>
#include <IL/il.h>
#define ILUT_USE_OPENGL
#include <IL/ilut.h>
#include <GL/glu.h>
#include "texture.h"
#include "deps/newclass.h"

int luaopen_texture(lua_State* L)
{
  const char* superclasses[] = {
    NULL
  };
  const luaL_Reg methods[] = {
    {"initialize", texture_initialize},
    {"destroy",    texture_destroy},
    {"name",       texture_name},
    {"smooth",     texture_smooth},
    {"size",       texture_size},
    {"draw",       texture_draw},
    {NULL, NULL}
  };
	class(L, "Texture", superclasses, texture_allocator, methods);
	return 0;
}

int texture_allocator(lua_State* L)
{
  /*
  1: metatable
  */
  lua_newuserdata(L, sizeof(Texture)); /* 2: userdata */
  lua_pushvalue(L, -2);                /* 3: metatable */
  lua_setmetatable(L, -2);             /* 2: userdata */
  return 1;
}

int texture_initialize(lua_State* L)
{
  /*
  1: texture
  2: filename
  */
  Texture* texture = lua_touserdata(L, 1);
  const char* filename = luaL_checkstring(L, 2);
  
  /* filename */
  texture->filename = malloc(sizeof(char) * (strlen(filename) + 1));
  strcpy(texture->filename, filename);
  
  /* id */
  ILboolean success;
  
  success = ilLoadImage((const ILstring) filename);
  if (!success)
  {
    lua_pushfstring(L, "Could not load image %s.", filename);
    lua_error(L);
  }
  
  texture->width = ilGetInteger(IL_IMAGE_WIDTH);
  texture->height = ilGetInteger(IL_IMAGE_HEIGHT);
  
  texture->id = ilutGLBindMipmaps();

  if (!glIsTexture(texture->id))
  {
    lua_pushfstring(L, "Could not load image %s.", filename);
    lua_error(L);
  }
  
  return 0;
}

int texture_destroy(lua_State* L)
{
  /*
  1: texture
  */
  Texture* texture = lua_touserdata(L, 1);
  free(texture->filename);
  glDeleteTextures(1, &texture->id);
  return 0;
}

int texture_name(lua_State* L)
{
  /*
  1: texture
  */
  Texture* texture = lua_touserdata(L, 1);
  lua_pushstring(L, texture->filename);
  return 1;
}

int texture_smooth(lua_State* L)
{
  /*
  1: texture
  2: smooth
  */
  Texture* texture = lua_touserdata(L, 1);
  int smooth = lua_toboolean(L, 2);
  glBindTexture(GL_TEXTURE_2D, texture->id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smooth ? GL_LINEAR : GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smooth ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST);
  return 0;
}

int texture_size(lua_State* L)
{
  /*
  1: texture
  */
  Texture* texture = lua_touserdata(L, 1);
  lua_pushinteger(L, texture->width);
  lua_pushinteger(L, texture->height);
  return 2;
}

int texture_draw(lua_State* L)
{
  /*
  1: texture
  2: x
  3: y
  4: (opt) scale x
  5: (opt) scale y
  6: (opt) rotation
  7: (opt) center x
  8: (opt) center y
  */
  Texture* texture = lua_touserdata(L, 1);
  float x = luaL_checknumber(L, 2);
  float y = luaL_checknumber(L, 3);
  float scale_x = luaL_optnumber(L, 4, 1);
  float scale_y = luaL_optnumber(L, 5, 1);
  float rotation = luaL_optnumber(L, 6, 0);
  float center_x = luaL_optnumber(L, 7, 0);
  float center_y = luaL_optnumber(L, 8, 0);
  
  static float vertices[8];
  vertices[0] = 0;
  vertices[1] = 0;
  vertices[2] = texture->width * scale_x;
  vertices[3] = vertices[1];
  vertices[4] = vertices[2];
  vertices[5] = texture->height * scale_y;
  vertices[6] = vertices[0];
  vertices[7] = vertices[5];
  
  static const float tex_coords[8] = {0,0, 0,1, 1,1, 1,0};
  
  glBindTexture(GL_TEXTURE_2D, texture->id);
  
  glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(rotation, 0, 0, 1);
    glTranslatef(-center_x, -center_y, 0);
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glTexCoordPointer(2, GL_FLOAT, 0, tex_coords);
    glDrawArrays(GL_QUADS, 0, 4);
  glPopMatrix();
  
  return 0;
}



#include <GL/gl.h>
#include <GL/glu.h>
#include <IL/il.h>
#define ILUT_USE_OPENGL
#include <IL/ilut.h>
#include <SDL/SDL.h>
#include <lua5.1/lauxlib.h>
#include "graphics.h"

int luaopen_graphics(lua_State* L)
{
  static const luaL_Reg graphics_lib[] = {
    {"open",              graphics_open},
    {"close",             graphics_close},
    {"desktopResolution", graphics_desktopResolution},
    {"beginFrame",        graphics_beginFrame},
    {"endFrame",          graphics_endFrame},
    {"clearColor",        graphics_clearColor},
    {NULL, NULL}
  };
  lua_newtable(L);
  luaL_register(L, NULL, graphics_lib);
  return 1;
}

int graphics_open(lua_State* L)
{
  /*
  1: width
  2: height
  3: title
  4: fullscreen
  5: resizable
  6: noframe
  */
  int width = luaL_checkint(L, 1);
  int height = luaL_checkint(L, 2);
  const char* title = luaL_checkstring(L, 3);
  int fullscreen = lua_toboolean(L, 4);
  int resizable = lua_toboolean(L, 5);
  int noframe = lua_toboolean(L, 6);
  
  ilInit();
  ilutInit();
  
  SDL_Init(SDL_INIT_VIDEO);
  
  Uint32 flags = SDL_OPENGL;
  if (fullscreen)
    flags |= SDL_FULLSCREEN;
  if (resizable)
    flags |= SDL_RESIZABLE;
  if (noframe)
    flags |= SDL_NOFRAME;
  
  
  SDL_SetVideoMode(width, height, 32, flags);
  SDL_WM_SetCaption(title, title);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, width, height, 0);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(0, 0, 0, 0);
  
  glEnable(GL_VERTEX_ARRAY);
  glEnable(GL_TEXTURE_COORD_ARRAY);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  return 0;
}

int graphics_close(lua_State* L)
{
  /*
  no param
  */
  SDL_Quit();
  return 0;
}

int graphics_desktopResolution(lua_State* L)
{
  /*
  no param
  */
  const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
  
  if (videoInfo == NULL)
  {
    lua_pushnil(L);
    lua_pushfstring(L, "SDL error: %s\n", SDL_GetError());
  }
  else
  {
    lua_pushinteger(L, videoInfo->current_w);
    lua_pushinteger(L, videoInfo->current_h);
  }
  return 2;
}

int graphics_beginFrame(lua_State* L)
{
  /*
  no param
  */
  glClear(GL_COLOR_BUFFER_BIT);
  return 0;
}

int graphics_endFrame(lua_State* L)
{
  /*
  no param
  */
  glFlush();
  SDL_GL_SwapBuffers();
  return 0;
}

int graphics_clearColor(lua_State* L)
{
  /*
  1: r
  2: g
  3: b
  */
  int r = luaL_checkint(L, 1);
  int g = luaL_checkint(L, 2);
  int b = luaL_checkint(L, 3);
  glClearColor(r / 255.f, g / 255.f, b / 255.f, 0);
  return 0;
}



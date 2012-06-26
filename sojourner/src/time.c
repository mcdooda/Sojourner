#include <stdio.h>
#include <SDL/SDL.h>
#include <lua5.1/lauxlib.h>
#include "time.h"

static struct {
  float begin;
  float elapsed;
  float frameDuration;
} time_state = {
  .begin         = 0,
  .elapsed       = 0,
  .frameDuration = 1.f / 60
};

int luaopen_time(lua_State* L)
{
  static const luaL_reg time_lib[] = {
    {"total",            time_total},
    {"elapsed",          time_elapsed},
    {"beginFrame",       time_beginFrame},
    {"endFrame",         time_endFrame},
    {"beginUpdate",      time_beginUpdate},
    {"endUpdate",        time_endUpdate},
    {"setFrameRate",     time_setFrameRate},
    {"frameRate",        time_frameRate},
    {"realFrameRate",    time_realFrameRate},
    {"frameDuration",    time_frameDuration},
    {"setFrameDuration", time_setFrameDuration},
    {NULL, NULL}
  };
  lua_newtable(L);
  luaL_register(L, NULL, time_lib);
  return 1;
}

int time_total(lua_State* L)
{
  /*
  no param
  */
  lua_pushnumber(L, get_time());
  return 1;
}

int time_elapsed(lua_State* L)
{
  /*
  no param
  */
  lua_pushnumber(L, time_state.elapsed);
  return 1;
}

int time_beginFrame(lua_State* L)
{
  /*
  no param
  */
  time_state.begin = get_time();
  return 0;
}

int time_endFrame(lua_State* L)
{
  /*
  no param
  */
  float end = get_time();
  time_state.elapsed = end - time_state.begin;
  if (time_state.elapsed < time_state.frameDuration)
  {
    sleeps(time_state.frameDuration - time_state.elapsed);
    time_state.elapsed = time_state.frameDuration;
  }
  return 0;
}

int time_beginUpdate(lua_State* L)
{
  time_state.begin = get_time();
  return 0;
}

int time_endUpdate(lua_State* L)
{
  time_state.elapsed = get_time() - time_state.begin;
  return 0;
}

int time_setFrameRate(lua_State* L)
{
  /*
  1: frame rate
  */
  time_state.frameDuration = 1.f / luaL_checknumber(L, 1);
  return 0;
}

int time_frameRate(lua_State* L)
{
  /*
  no param
  */
  lua_pushnumber(L, 1.f / time_state.frameDuration);
  return 1;
}

int time_realFrameRate(lua_State* L)
{
  /*
  no param
  */
  lua_pushnumber(L, 1.f / time_state.elapsed);
  return 1;
}

int time_frameDuration(lua_State* L)
{
  /*
  no param
  */
  lua_pushnumber(L, time_state.frameDuration);
  return 1;
}

int time_setFrameDuration(lua_State* L)
{
  /*
  no param
  */
  time_state.frameDuration = luaL_checknumber(L, 1);
  return 0;
}

float get_time()
{
  return SDL_GetTicks() / 1000.f;
}

void sleeps(float duration)
{
  SDL_Delay((Uint32)(duration * 1000));
}



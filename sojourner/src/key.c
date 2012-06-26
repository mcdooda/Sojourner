#include <SDL/SDL.h>
#include "key.h"

int luaopen_key(lua_State* L)
{
  lua_newtable(L);
  struct {
    const char* name;
    int code;
  } keys[] = {
    {"up",     SDLK_UP},
    {"down",   SDLK_DOWN},
    {"left",   SDLK_LEFT},
    {"right",  SDLK_RIGHT},
    {"escape", SDLK_ESCAPE},
    {NULL, 0}
  };
  int i;
  for (i = 0; keys[i].name != NULL; i++)
  {
    lua_pushinteger(L, keys[i].code);
    lua_setfield(L, -2, keys[i].name);
  }
  return 1;
}



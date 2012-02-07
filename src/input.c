#include <GL/glu.h>
#include <lua5.1/lauxlib.h>
#include "input.h"

static struct
{
  int closed;
  
  Uint8* currentKeyboardState;
  Uint8* previousKeyboardState;
  int numKeys;
  
  Uint8 currentMouseState;
  Uint8 previousMouseState;
  int mouseX;
  int mouseY;
  
} input_state = {
  .closed = 0,
  
  .currentKeyboardState = NULL,
  .previousKeyboardState = NULL,
  .numKeys = 0,
  
  .currentMouseState = 0,
  .previousMouseState = 0,
  .mouseX = 0,
  .mouseY = 0
};

int luaopen_input(lua_State* L)
{
  static const luaL_Reg input_lib[] = {
    {"open",             input_open},
    {"close",            input_close},
    {"poll",             input_poll},
    {"wait",             input_wait},
    {"pointer",          input_pointer},
    {"pressed",          input_pressed},
    {"justPressed",      input_justPressed},
    {"mousePressed",     input_mousePressed},
    {"mouseJustPressed", input_mouseJustPressed},
    {"closed",           input_closed},
    {NULL, NULL}
  };
  lua_newtable(L);
  luaL_register(L, NULL, input_lib);
  return 1;
}

int input_open(lua_State* L)
{
  /*
  no param
  */
  SDL_GetKeyState(&input_state.numKeys);
  input_state.currentKeyboardState = calloc(input_state.numKeys, sizeof(Uint8));
  input_state.previousKeyboardState = calloc(input_state.numKeys, sizeof(Uint8));
  return 0;
}

int input_close(lua_State* L)
{
  /*
  no param
  */
  free(input_state.currentKeyboardState);
  free(input_state.previousKeyboardState);
  return 0;
}

int input_poll(lua_State* L)
{
  /*
  no param
  */
  SDL_Event event;
  while (SDL_PollEvent(&event))
    handle_event(event);
  
  copy_keyboard_state(input_state.currentKeyboardState, input_state.previousKeyboardState);  
  copy_keyboard_state(SDL_GetKeyState(NULL), input_state.currentKeyboardState);
  
  input_state.previousMouseState = input_state.currentMouseState;
  input_state.currentMouseState = SDL_GetMouseState(&input_state.mouseX, &input_state.mouseY);
  
  return 0;
}

int input_wait(lua_State* L)
{
  /*
  no param
  */
  SDL_Event event;
  SDL_WaitEvent(&event);
  handle_event(event);
  
  input_poll(L); /* warning: might be dangerous! */
    
  return 0;
}

int input_pressed(lua_State* L)
{
  /*
  1: key code (int or string)
  */
  int code;
  int type = lua_type(L, 1);
  
  if (type == LUA_TNUMBER)
    code = lua_tointeger(L, 1);
    
  else if (type == LUA_TSTRING)
    code = lua_tostring(L, 1)[0]; /* 1st letter */
    
  else
    luaL_argcheck(L, 0, 1, "must be an integer or a string");
  
  lua_pushboolean(L, input_state.currentKeyboardState[code]);
  return 1;
}

int input_justPressed(lua_State* L)
{
  /*
  1: key code (int or string)
  */
  int code;
  int type = lua_type(L, 1);
  
  if (type == LUA_TNUMBER)
    code = lua_tointeger(L, 1);
    
  else if (type == LUA_TSTRING)
    code = lua_tostring(L, 1)[0]; /* 1st letter */
    
  else
    luaL_argcheck(L, 0, 1, "must be an integer or a string");
  
  lua_pushboolean(L, input_state.currentKeyboardState[code] && !input_state.previousKeyboardState[code]);
  return 1;
}

int input_mousePressed(lua_State* L)
{
  /*
  1: button code
  */
  int button = luaL_checkint(L, 1);
  int pressed = input_state.currentMouseState & SDL_BUTTON(button);
  lua_pushboolean(L, pressed);
  return 1;
}

int input_mouseJustPressed(lua_State* L)
{
  /*
  1: button code
  */
  int button = luaL_checkint(L, 1);
  int justPressed = (input_state.currentMouseState & SDL_BUTTON(button)) && !(input_state.previousMouseState & SDL_BUTTON(button));
  lua_pushboolean(L, justPressed);
  return 1;
}

int input_pointer(lua_State* L)
{
  /*
  no param
  */
  lua_pushinteger(L, input_state.mouseX);
  lua_pushinteger(L, input_state.mouseY);
  return 2;
}

int input_closed(lua_State* L)
{
  /*
  no param
  */
  lua_pushboolean(L, input_state.closed);
  return 1;
}

void handle_event(SDL_Event event)
{
  switch (event.type)
  {
    case SDL_QUIT:
    input_state.closed = 1;
    break;
    
    case SDL_KEYDOWN:
    if (event.key.keysym.sym == SDLK_ESCAPE)
      input_state.closed = 1;
    break;
    
    case SDL_VIDEORESIZE:
    glViewport(0, 0, event.resize.w, event.resize.h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, event.resize.w, event.resize.h, 0);
    glMatrixMode(GL_MODELVIEW);
    break;
  }
}

void copy_keyboard_state(Uint8* keyboardState, Uint8* dst)
{
  memcpy(dst, keyboardState, input_state.numKeys * sizeof(Uint8));
}



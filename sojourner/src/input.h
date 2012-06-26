#ifndef INPUT_H
 #define INPUT_H

#include <SDL/SDL.h>
#include <lua5.1/lua.h>

int luaopen_input(lua_State* L);

int input_open             (lua_State* L);
int input_close            (lua_State* L);
int input_poll             (lua_State* L);
int input_wait             (lua_State* L);
int input_pressed          (lua_State* L);
int input_justPressed      (lua_State* L);
int input_mousePressed     (lua_State* L);
int input_mouseJustPressed (lua_State* L);
int input_pointer          (lua_State* L);
int input_closed           (lua_State* L);

void handle_event(SDL_Event event);
void copy_keyboard_state(Uint8* keyboardState, Uint8* dst);

#endif

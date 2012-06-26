#include "newclass.h"

void class(lua_State* L, const char* name, const char* superclasses[], lua_CFunction allocator, const luaL_Reg methods[])
{
	lua_getglobal(L, "class");
	
	/* class name */
	lua_pushstring(L, name);
	
	/* gets class.Name function */
	lua_gettable(L, -2);
	
	/* class definition: super classes and methods */
	lua_newtable(L);
	
	int k = 1; /* integer key */
	
	/* extends */
	if (superclasses[0] != NULL)
	{
		lua_pushinteger(L, k++);
		
		lua_getglobal(L, "extends");
	
		int i;
		for (i = 0; superclasses[i] != NULL; i++)
			lua_pushstring(L, superclasses[i]);

		lua_call(L, i, 1);
		lua_settable(L, -3);
	}
	
	/* allocator */
	if (allocator != NULL)
	{
	  lua_pushinteger(L, k++);
	  
	  lua_getglobal(L, "allocator");
	  
	  lua_pushcfunction(L, allocator);
	  lua_call(L, 1, 1);
	  lua_settable(L, -3);
	}
	
	/* methods */
	int i;
	for (i = 0; methods[i].name != NULL; i++)
	{
		lua_pushcfunction(L, methods[i].func);
		lua_setfield(L, -2, methods[i].name);
	}
	
	lua_call(L, 1, 0);
}



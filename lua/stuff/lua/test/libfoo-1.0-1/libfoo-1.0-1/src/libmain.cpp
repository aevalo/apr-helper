#include <iostream>

#define LUA_BUILD_AS_DLL
#define LUA_LIB
#include "lua.hpp"
#define PROJECT_MODULENAME "myhello"

extern "C" {
	int LUA_API luaopen_myhello (lua_State *L);
}

namespace {
  int index(lua_State *L)
  {
    for (int i = lua_gettop(L); i > 0; i--)
      std::cout << "Stack at " << i << ": " << lua_typename(L, i) << std::endl;
    return 0;
  }
  
  int newindex(lua_State *L)
  {
    for (int i = lua_gettop(L); i > 0; i--)
      std::cout << "Stack at " << i << ": " << lua_typename(L, i) << std::endl;
    return 0;
  }
  
  int call(lua_State *L)
  {
    for (int i = lua_gettop(L); i > 0; i--)
      std::cout << "Stack at " << i << ": " << lua_typename(L, i) << std::endl;
    return 0;
  }
  
  int helloworld(lua_State* L)
  {
    std::cout << "Hello, World!!!" << std::endl;
    return 0;
  }
  
  int init_myhello(lua_State* L)
  {
    lua_newtable(L);
    int mytable = lua_gettop(L);
    lua_pushstring(L, "greet");
    lua_pushcfunction(L, helloworld);
    lua_settable(L, mytable);
    lua_pushstring(L, "foo");
    lua_pushstring(L, "baz");
    lua_settable(L, mytable);
    std::cout << "mytable => " << mytable << std::endl;
    
    lua_newtable(L);
    int mymetatable = lua_gettop(L);
    lua_pushstring(L, "__newindex");
    lua_pushcfunction(L, newindex);
    lua_settable(L, mymetatable);
    lua_pushstring(L, "__index");
    lua_pushcfunction(L, index);
    lua_settable(L, mymetatable);
    lua_pushstring(L, "__call");
    lua_pushcfunction(L, call);
    lua_settable(L, mymetatable);
    lua_setmetatable(L, mytable);
    std::cout << "mymetatable => " << mymetatable << std::endl;
    return 1;
  }
}

int LUA_API luaopen_myhello (lua_State *L) {
	struct luaL_reg driver[] = {
		{"InitMyHello", init_myhello},		
		{NULL, NULL},
	};
	luaL_openlib(L, PROJECT_MODULENAME, driver, 0);
	return 1;
}

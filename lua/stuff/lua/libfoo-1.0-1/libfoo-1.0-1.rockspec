package = "libfoo"
version = '1.0-1'

source = {
   url = "libfoo-1.0-1.tar.gz"
}

description = {
   summary = "An example for the LuaRocks tutorial.",
   detailed = [[
      This is an example for the LuaRocks tutorial.
      Here we would put a detailed, typically
      paragraph-long description.
   ]],
   homepage = "http://me.github.com/luafruits",
   license = "MIT/X11"
}
dependencies = {
   "lua >= 5.1"
}
build = {
   type = "cmake",
   modules = {
      foo = {
         sources = {"src/libfoo.cpp", "src/Foo.hpp"}
      },
      mylib = {
         sources = {"src/libmain.cpp"}
      }
   },
   ["fun.lua"] = "fun.lua",
   ["test_mylib.lua"] = "test_mylib.lua"
}

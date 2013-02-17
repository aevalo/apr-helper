package = "zst"
version = "1.0-1"
source = {
   url = "zst-1.0-1.tar.bz2"
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
   "lua >= 5.1" --,
--   "luaknife"
}
external_dependencies = {
--   LIBDATE = {
--      header = "libdate.h"
--   }
}
build = {
   type = "builtin",
   modules = {
--      apricot = "src/apricot.lua",
--      ["apricot.seeds"] = "src/apricot/seeds.lua",
--      banana = "src/banana.c",
--      cherry = {"src/cherry.c", "src/cherry_pie.c"},
--      date = {
--         sources = {"src/date.c", "src/cali_date.c", "src/arab_date.c"},
--         defines = {"MAX_DATES_PER_MEAL=50"}
--         libraries = {"date"},
--         incdirs = {"$(LIBDATE_INCDIR)"},
--         libdirs = {"$(LIBDATE_LIBDIR)"}
--      }
      zst = "src/zstring.c"
   }
  
}
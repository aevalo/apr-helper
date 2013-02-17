#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

/* gcc general.c -Wall -shared -o general.so */

/* system */
static int zst_exec(lua_State *L)
{
        int status;
    status = system(lua_tostring(L, 1));
    lua_pushnumber(L, status);
    return 1;
}

/* mkdir */
static int zst_mkdir(lua_State *L)
{
        int status;
        mode_t mode = lua_tonumber(L, 2);
        status = mkdir(lua_tostring(L, 1), mode);
        lua_pushnumber(L, status);
        return 1;
}

/* symlink */ 
static int zst_symlink(lua_State *L)
{
        int status;
        const char *old = lua_tostring(L, 1);
        const char *new = lua_tostring(L, 2);
        status = symlink(old, new);
        lua_pushnumber(L, status);
        return 1;
}

/* rmdir */
static int zst_rmdir(lua_State *L)
{
        int status;
        status = rmdir(lua_tostring(L, 1));
        lua_pushnumber(L, status);
        return 1;
}

/* rename */
static int zst_rename(lua_State *L)
{
    int status;
    const char *old = lua_tostring(L, 1);
    const char *new = lua_tostring(L, 2);
    status = rename(old, new);
    lua_pushnumber(L, status);
    return 1;   
}

/* remove */
static int zst_remove(lua_State *L)
{
        int status;
        const char *filename = lua_tostring(L, 1);
        status = remove(filename);
        lua_pushnumber(L, status);
        return 1;
}

/* chown */
static int zst_chown(lua_State *L)
{
    int status;
    const char *filename = lua_tostring(L, 1);
    uid_t owner = lua_tonumber(L, 2);
    gid_t group = lua_tonumber(L, 3);
    status = chown(filename, owner, group);
    lua_pushnumber(L, status);
    return 1;   
}

/* chmod */
static int zst_chmod(lua_State *L)
{
    int status;
    const char *filename = lua_tostring(L, 1);
    mode_t mode = lua_tonumber(L, 2);
    status = chmod(filename, mode);
    lua_pushnumber(L, status);
    return 1;

}

/* get_current_dir_name */
static int zst_getcwd(lua_State *L)
{
    char *dir;
    dir = get_current_dir_name();
    lua_pushstring(L, dir);
    return 1;
}

static int zst_strlen(lua_State *L)
{
    size_t len;
    len = strlen(lua_tostring(L, 1));
    lua_pushnumber(L, len);
    return 1;
}

int luaopen_zst(lua_State *L) 
{
    lua_register(L,"zst_exec", zst_exec);
    lua_register(L,"zst_mkdir", zst_mkdir);
    lua_register(L,"zst_symlink", zst_symlink);
    lua_register(L,"zst_rmdir", zst_rmdir);
    lua_register(L,"zst_rename", zst_rename);
    lua_register(L,"zst_remove", zst_remove);
    lua_register(L,"zst_chown", zst_chown);
    lua_register(L,"zst_chmod", zst_chmod);
    lua_register(L,"zst_getcwd", zst_getcwd);
    lua_register(L,"zst_strlen", zst_strlen);

    return 0;
}
#include "PluginAdMobLua.hpp"
#include "PluginAdMob/PluginAdMob.h"
#include "tolua_fix.h"
#include "SDKBoxLuaHelper.h"
#include "sdkbox/Sdkbox.h"



int lua_PluginAdMobLua_PluginAdMob_getCurrBannerHeight(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginAdMob",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginAdMobLua_PluginAdMob_getCurrBannerHeight'", nullptr);
            return 0;
        }
        int ret = sdkbox::PluginAdMob::getCurrBannerHeight();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginAdMob:getCurrBannerHeight",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginAdMobLua_PluginAdMob_getCurrBannerHeight'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginAdMobLua_PluginAdMob_hide(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginAdMob",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.PluginAdMob:hide");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginAdMobLua_PluginAdMob_hide'", nullptr);
            return 0;
        }
        sdkbox::PluginAdMob::hide(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginAdMob:hide",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginAdMobLua_PluginAdMob_hide'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginAdMobLua_PluginAdMob_setTestDevices(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginAdMob",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.PluginAdMob:setTestDevices");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginAdMobLua_PluginAdMob_setTestDevices'", nullptr);
            return 0;
        }
        sdkbox::PluginAdMob::setTestDevices(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginAdMob:setTestDevices",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginAdMobLua_PluginAdMob_setTestDevices'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginAdMobLua_PluginAdMob_show(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginAdMob",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.PluginAdMob:show");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginAdMobLua_PluginAdMob_show'", nullptr);
            return 0;
        }
        sdkbox::PluginAdMob::show(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginAdMob:show",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginAdMobLua_PluginAdMob_show'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginAdMobLua_PluginAdMob_cache(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginAdMob",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.PluginAdMob:cache");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginAdMobLua_PluginAdMob_cache'", nullptr);
            return 0;
        }
        sdkbox::PluginAdMob::cache(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginAdMob:cache",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginAdMobLua_PluginAdMob_cache'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginAdMobLua_PluginAdMob_getCurrBannerWidth(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginAdMob",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginAdMobLua_PluginAdMob_getCurrBannerWidth'", nullptr);
            return 0;
        }
        int ret = sdkbox::PluginAdMob::getCurrBannerWidth();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginAdMob:getCurrBannerWidth",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginAdMobLua_PluginAdMob_getCurrBannerWidth'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginAdMobLua_PluginAdMob_init(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginAdMob",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginAdMobLua_PluginAdMob_init'", nullptr);
            return 0;
        }
        bool ret = sdkbox::PluginAdMob::init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginAdMob:init",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginAdMobLua_PluginAdMob_init'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginAdMobLua_PluginAdMob_getVersion(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginAdMob",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginAdMobLua_PluginAdMob_getVersion'", nullptr);
            return 0;
        }
        std::string ret = sdkbox::PluginAdMob::getVersion();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginAdMob:getVersion",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginAdMobLua_PluginAdMob_getVersion'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginAdMobLua_PluginAdMob_isAvailable(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginAdMob",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.PluginAdMob:isAvailable");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginAdMobLua_PluginAdMob_isAvailable'", nullptr);
            return 0;
        }
        bool ret = sdkbox::PluginAdMob::isAvailable(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginAdMob:isAvailable",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginAdMobLua_PluginAdMob_isAvailable'.",&tolua_err);
#endif
    return 0;
}
static int lua_PluginAdMobLua_PluginAdMob_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PluginAdMob)");
    return 0;
}

int lua_register_PluginAdMobLua_PluginAdMob(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"sdkbox.PluginAdMob");
    tolua_cclass(tolua_S,"PluginAdMob","sdkbox.PluginAdMob","",nullptr);

    tolua_beginmodule(tolua_S,"PluginAdMob");
        tolua_function(tolua_S,"getCurrBannerHeight", lua_PluginAdMobLua_PluginAdMob_getCurrBannerHeight);
        tolua_function(tolua_S,"hide", lua_PluginAdMobLua_PluginAdMob_hide);
        tolua_function(tolua_S,"setTestDevices", lua_PluginAdMobLua_PluginAdMob_setTestDevices);
        tolua_function(tolua_S,"show", lua_PluginAdMobLua_PluginAdMob_show);
        tolua_function(tolua_S,"cache", lua_PluginAdMobLua_PluginAdMob_cache);
        tolua_function(tolua_S,"getCurrBannerWidth", lua_PluginAdMobLua_PluginAdMob_getCurrBannerWidth);
        tolua_function(tolua_S,"init", lua_PluginAdMobLua_PluginAdMob_init);
        tolua_function(tolua_S,"getVersion", lua_PluginAdMobLua_PluginAdMob_getVersion);
        tolua_function(tolua_S,"isAvailable", lua_PluginAdMobLua_PluginAdMob_isAvailable);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(sdkbox::PluginAdMob).name();
    g_luaType[typeName] = "sdkbox.PluginAdMob";
    g_typeCast["PluginAdMob"] = "sdkbox.PluginAdMob";
    return 1;
}
TOLUA_API int register_all_PluginAdMobLua(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"sdkbox",0);
	tolua_beginmodule(tolua_S,"sdkbox");

	lua_register_PluginAdMobLua_PluginAdMob(tolua_S);

	tolua_endmodule(tolua_S);

	sdkbox::setProjectType("lua");
	return 1;
}


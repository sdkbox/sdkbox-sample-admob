
#include "PluginAdMobLuaHelper.h"
#include "PluginAdMob/PluginAdMob.h"
#include "SDKBoxLuaHelper.h"

class AdMobListenerLua : public sdkbox::AdMobListener {
public:
    AdMobListenerLua(): mLuaHandler(0) {
    }

    ~AdMobListenerLua() {
        resetHandler();
    }

    void setHandler(int luaHandler) {
        if (mLuaHandler == luaHandler) {
            return;
        }
        resetHandler();
        mLuaHandler = luaHandler;
    }

    void resetHandler() {
        if (0 == mLuaHandler) {
            return;
        }

        LUAENGINE->removeScriptHandler(mLuaHandler);
        mLuaHandler = 0;
    }

    void adViewDidReceiveAd(const std::string &name) {
        LuaStack* stack = LUAENGINE->getLuaStack();
        LuaValueDict dict;

        dict.insert(std::make_pair("event", LuaValue::stringValue("adViewDidReceiveAd")));
        dict.insert(std::make_pair("name", LuaValue::stringValue(name)));

        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }
    void adViewDidFailToReceiveAdWithError(const std::string &name, const std::string &msg) {
        LuaStack* stack = LUAENGINE->getLuaStack();
        LuaValueDict dict;

        dict.insert(std::make_pair("event", LuaValue::stringValue("adViewDidFailToReceiveAdWithError")));
        dict.insert(std::make_pair("name", LuaValue::stringValue(name)));
        dict.insert(std::make_pair("msg", LuaValue::stringValue(msg)));

        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }
    void adViewWillPresentScreen(const std::string &name) {
        LuaStack* stack = LUAENGINE->getLuaStack();
        LuaValueDict dict;

        dict.insert(std::make_pair("event", LuaValue::stringValue("adViewWillPresentScreen")));
        dict.insert(std::make_pair("name", LuaValue::stringValue(name)));

        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }
    void adViewDidDismissScreen(const std::string &name) {
        LuaStack* stack = LUAENGINE->getLuaStack();
        LuaValueDict dict;

        dict.insert(std::make_pair("event", LuaValue::stringValue("adViewDidDismissScreen")));
        dict.insert(std::make_pair("name", LuaValue::stringValue(name)));

        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }
    void adViewWillDismissScreen(const std::string &name) {
        LuaStack* stack = LUAENGINE->getLuaStack();
        LuaValueDict dict;

        dict.insert(std::make_pair("event", LuaValue::stringValue("adViewWillDismissScreen")));
        dict.insert(std::make_pair("name", LuaValue::stringValue(name)));

        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }
    void adViewWillLeaveApplication(const std::string &name) {
        LuaStack* stack = LUAENGINE->getLuaStack();
        LuaValueDict dict;

        dict.insert(std::make_pair("event", LuaValue::stringValue("adViewWillLeaveApplication")));
        dict.insert(std::make_pair("name", LuaValue::stringValue(name)));

        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }

private:
    int mLuaHandler;
};

int lua_PluginAdMobLua_PluginAdMob_setListener(lua_State* tolua_S) {
    int argc = 0;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginAdMob",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S, 2 , "LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        AdMobListenerLua* lis = static_cast<AdMobListenerLua*> (sdkbox::PluginAdMob::getListener());
        if (NULL == lis) {
            lis = new AdMobListenerLua();
        }
        lis->setHandler(handler);
        sdkbox::PluginAdMob::setListener(lis);

        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginAdMob::setListener",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginAdMobLua_PluginAdMob_setListener'.",&tolua_err);
#endif
    return 0;
}

static int lua_createTable(lua_State* L, const std::map<std::string, int>& map) {
    lua_newtable(L);

    std::map<std::string, int>::const_iterator it = map.begin();
    while (it != map.end()) {
        lua_pushstring(L, it->first.c_str());
        lua_pushinteger(L, it->second);
        lua_settable(L, -3);
        it++;
    }

    return 1;
}

static int lua_setTable(lua_State* L, int table, const std::string& name, const std::map<std::string, int>& map) {
    if (table < 0) {
        table = lua_gettop(L) + table + 1;
    }
    lua_pushstring(L, name.c_str());
    lua_createTable(L, map);
    lua_rawset(L, table);

    return 0;
}

int lua_PluginAdMobLua_constants(lua_State* L) {
    if (NULL == L) {
        return 0;
    }

    // lua_pushstring(L, "sdkbox.PluginAdMob");
    // lua_rawget(L, LUA_REGISTRYINDEX);
    // if (lua_istable(L,-1)) {

    //     std::map<std::string, int> enums;
    //     enums.clear();
    //     enums.insert(std::make_pair("kIMSDKGenderMale", 1));
    //     enums.insert(std::make_pair("kIMSDKGenderFemale", 2));
    //     lua_setTable(L, -1, "SBIMSDKGender", enums);
    // }
    // lua_pop(L, 1);

    return 1;
}

int extern_PluginAdMob(lua_State* L) {
    if (NULL == L) {
        return 0;
    }

    lua_pushstring(L, "sdkbox.PluginAdMob");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L,"setListener", lua_PluginAdMobLua_PluginAdMob_setListener);
    }
     lua_pop(L, 1);

    lua_PluginAdMobLua_constants(L);

    return 1;
}

TOLUA_API int register_all_PluginAdMobLua_helper(lua_State* L) {
    tolua_module(L,"sdkbox",0);
    tolua_beginmodule(L,"sdkbox");

    extern_PluginAdMob(L);

    tolua_endmodule(L);
    return 1;
}




#include "SDKBoxLuaHelper.h"
#include "sdkbox/Sdkbox.h"

#include <limits>

#if COCOS2D_VERSION >= 0x00030000

#else

std::map<std::string, std::string>  g_luaType;
std::map<std::string, std::string>  g_typeCast;

#if COCOS2D_DEBUG >=1
void luaval_to_native_err(lua_State* L,const char* msg,tolua_Error* err, const char* funcName)
{
    if (NULL == L || NULL == err || NULL == msg || 0 == strlen(msg))
        return;

    if (msg[0] == '#')
    {
        const char* expected = err->type;
        const char* provided = tolua_typename(L,err->index);
        if (msg[1]=='f')
        {
            int narg = err->index;
            if (err->array)
                CCLOG("%s\n     %s argument #%d is array of '%s'; array of '%s' expected.\n",msg+2,funcName,narg,provided,expected);
            else
                CCLOG("%s\n     %s argument #%d is '%s'; '%s' expected.\n",msg+2,funcName,narg,provided,expected);
        }
        else if (msg[1]=='v')
        {
            if (err->array)
                CCLOG("%s\n     %s value is array of '%s'; array of '%s' expected.\n",funcName,msg+2,provided,expected);
            else
                CCLOG("%s\n     %s value is '%s'; '%s' expected.\n",msg+2,funcName,provided,expected);
        }
    }
}
#endif

bool luaval_to_ushort(lua_State* L, int lo, unsigned short* outValue, const char* funcName)
{
    if (NULL == L || NULL == outValue)
        return false;

    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        *outValue = (unsigned short)tolua_tonumber(L, lo, 0);
    }

    return ok;
}


bool luaval_to_int32(lua_State* L,int lo,int* outValue, const char* funcName)
{
    if (NULL == L || NULL == outValue)
        return false;

    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        /**
         When we want to convert the number value from the Lua to int, we would call lua_tonumber to implement.It would
         experience two phase conversion: int -> double, double->int.But,for the 0x80000000 which the min value of int, the
         int cast may return an undefined result,like 0x7fffffff.So we must use the (int)(unsigned int)lua_tonumber() to get
         predictable results for 0x80000000.In this place,we didn't use lua_tointeger, because it may produce differen results
         depending on the compiler,e.g:for iPhone4s,it also get wrong value for 0x80000000.
         */
        unsigned int estimateValue = (unsigned int)lua_tonumber(L, lo);
        if (estimateValue == std::numeric_limits<int>::min())
        {
            *outValue = (int)estimateValue;
        }
        else
        {
            *outValue = (int)lua_tonumber(L, lo);
        }
    }

    return ok;
}

bool luaval_to_uint32(lua_State* L, int lo, unsigned int* outValue, const char* funcName)
{
    if (NULL == L || NULL == outValue)
        return false;

    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        *outValue = (unsigned int)tolua_tonumber(L, lo, 0);
    }

    return ok;
}

bool luaval_to_uint16(lua_State* L,int lo,uint16_t* outValue, const char* funcName)
{
    if (NULL == L || NULL == outValue)
        return false;

    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        *outValue = (unsigned char)tolua_tonumber(L, lo, 0);
    }

    return ok;
}

bool luaval_to_boolean(lua_State* L,int lo,bool* outValue, const char* funcName)
{
    if (NULL == L || NULL == outValue)
        return false;

    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isboolean(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        *outValue = (bool)tolua_toboolean(L, lo, 0);
    }

    return ok;
}

bool luaval_to_number(lua_State* L,int lo,double* outValue, const char* funcName)
{
    if (NULL == L || NULL == outValue)
        return false;

    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        *outValue = tolua_tonumber(L, lo, 0);
    }

    return ok;
}

bool luaval_to_long_long(lua_State* L,int lo,long long* outValue, const char* funcName)
{
    if (NULL == L || NULL == outValue)
        return false;

    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        *outValue = (long long)tolua_tonumber(L, lo, 0);
    }

    return ok;
}

bool luaval_to_std_string(lua_State* L, int lo, std::string* outValue, const char* funcName)
{
    if (NULL == L || NULL == outValue)
        return false;

    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_iscppstring(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        *outValue = tolua_tocppstring(L,lo,NULL);
    }

    return ok;
}

bool luaval_to_std_vector_string(lua_State* L, int lo, std::vector<std::string>* ret, const char* funcName)
{
    if (NULL == L || NULL == ret || lua_gettop(L) < lo)
        return false;

    tolua_Error tolua_err;
    bool ok = true;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        std::string value = "";
        for (size_t i = 0; i < len; i++)
        {
            lua_pushnumber(L, i + 1);
            lua_gettable(L,lo);
            if(lua_isstring(L, -1))
            {
                ok = luaval_to_std_string(L, -1, &value);
                if(ok)
                    ret->push_back(value);
            }
            else
            {
                //                CCASSERT(false, "string type is needed");
            }

            lua_pop(L, 1);
        }
    }

    return ok;
}

bool luaval_to_std_vector_int(lua_State* L, int lo, std::vector<int>* ret, const char* funcName)
{
    if (NULL == L || NULL == ret || lua_gettop(L) < lo)
        return false;

    tolua_Error tolua_err;
    bool ok = true;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        for (size_t i = 0; i < len; i++)
        {
            lua_pushnumber(L, i + 1);
            lua_gettable(L,lo);
            if(lua_isnumber(L, -1))
            {
                ret->push_back((int)tolua_tonumber(L, -1, 0));
            }
            else
            {
                //                CCASSERT(false, "int type is needed");
            }

            lua_pop(L, 1);
        }
    }

    return ok;
}

bool luaval_to_std_vector_float(lua_State* L, int lo, std::vector<float>* ret, const char* funcName)
{
    if (NULL == L || NULL == ret || lua_gettop(L) < lo)
        return false;

    tolua_Error tolua_err;
    bool ok = true;

    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        for (size_t i = 0; i < len; i++)
        {
            lua_pushnumber(L, i + 1);
            lua_gettable(L,lo);
            if(lua_isnumber(L, -1))
            {
                ret->push_back((float)tolua_tonumber(L, -1, 0));
            }
            else
            {
                //                CCASSERT(false, "float type is needed");
            }

            lua_pop(L, 1);
        }
    }

    return ok;
}


bool luaval_to_std_vector_ushort(lua_State* L, int lo, std::vector<unsigned short>* ret, const char* funcName)
{
    if (NULL == L || NULL == ret || lua_gettop(L) < lo)
        return false;

    tolua_Error tolua_err;
    bool ok = true;

    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        for (size_t i = 0; i < len; i++)
        {
            lua_pushnumber(L, i + 1);
            lua_gettable(L,lo);
            if(lua_isnumber(L, -1))
            {
                ret->push_back((unsigned short)tolua_tonumber(L, -1, 0));
            }
            else
            {
                //                CCASSERT(false, "unsigned short type is needed");
            }

            lua_pop(L, 1);
        }
    }

    return ok;
}

void ccvector_std_string_to_luaval(lua_State* L, const std::vector<std::string>& inValue)
{
    if (NULL == L)
        return;

    lua_newtable(L);

    int index = 1;
    for (size_t i = 0; i < inValue.size(); i++)
    {
        lua_pushnumber(L, (lua_Number)index);
        lua_pushstring(L, inValue[i].c_str());
        lua_rawset(L, -3);
        ++index;
    }
}

void ccvector_int_to_luaval(lua_State* L, const std::vector<int>& inValue)
{
    if (NULL == L)
        return;

    lua_newtable(L);

    int index = 1;
    for (size_t i = 0; i < inValue.size(); i++)
    {
        lua_pushnumber(L, (lua_Number)index);
        lua_pushnumber(L, (lua_Number)inValue[i]);
        lua_rawset(L, -3);
        ++index;
    }
}

void ccvector_float_to_luaval(lua_State* L, const std::vector<float>& inValue)
{
    if (NULL == L)
        return;

    lua_newtable(L);

    int index = 1;
    for (size_t i = 0; i < inValue.size(); i++)
    {
        lua_pushnumber(L, (lua_Number)index);
        lua_pushnumber(L, (lua_Number)inValue[i]);
        lua_rawset(L, -3);
        ++index;
    }
}

void ccvector_ushort_to_luaval(lua_State* L, const std::vector<unsigned short>& inValue)
{
    if (NULL == L)
        return;

    lua_newtable(L);

    int index = 1;
    for (size_t i = 0; i < inValue.size(); i++)
    {
        lua_pushnumber(L, (lua_Number)index);
        lua_pushnumber(L, (lua_Number)inValue[i]);
        lua_rawset(L, -3);
        ++index;
    }
}

#endif

bool luaval_to_ccluavaluemap(lua_State* L, int lo, LuaValueDict* ret, const char* funcName)
{
    if ( nullptr == L || nullptr == ret)
        return false;

    tolua_Error tolua_err;
    bool ok = true;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if COCOS2D_DEBUG >=1
        // luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }

    if (ok)
    {
        std::string stringKey = "";
        std::string stringValue = "";
        bool boolVal = false;
        LuaValueDict& dict = *ret;
        lua_pushnil(L);                                             /* first key L: lotable ..... nil */
        while ( 0 != lua_next(L, lo ) )                             /* L: lotable ..... key value */
        {
            if (!lua_isstring(L, -2))
            {
                lua_pop(L, 1);                                      /* removes 'value'; keep 'key' for next iteration*/
                continue;
            }

            if(luaval_to_std_string(L, -2, &stringKey))
            {

                if(lua_istable(L, -1))
                {
                    lua_pushnumber(L,1);
                    lua_gettable(L,-2);

                    if (lua_isnil(L, -1) )                          /** if table[1] = nil,we don't think it is a pure array */
                    {
                        lua_pop(L,1);
                        LuaValueDict dictVal;
                        if (luaval_to_ccluavaluemap(L, lua_gettop(L), &dictVal))
                        {
                            dict[stringKey] = LuaValue::dictValue(dictVal);
                        }
                    }
                    else
                    {
                        lua_pop(L,1);
                        LuaValueArray arrVal;
                        if (luaval_to_ccluavaluevector(L, lua_gettop(L), &arrVal))
                        {
                            dict[stringKey] = LuaValue::arrayValue(arrVal);
                        }
                    }
                }
                else if(lua_type(L, -1) == LUA_TSTRING)
                {
                    if(luaval_to_std_string(L, -1, &stringValue))
                    {
                        dict[stringKey] = LuaValue::stringValue(stringValue);
                    }
                }
                else if(lua_type(L, -1) == LUA_TBOOLEAN)
                {
                    if (luaval_to_boolean(L, -1, &boolVal))
                    {
                        dict[stringKey] = LuaValue::booleanValue(boolVal);
                    }
                }
                else if(lua_type(L, -1) == LUA_TNUMBER)
                {
                    dict[stringKey] = LuaValue::floatValue(tolua_tonumber(L, -1, 0));
                }
                else
                {
                    //                    CCASSERT(false, "not supported type");
                }
            }

            lua_pop(L, 1);                                          /* L: lotable ..... key */
        }
    }

    return ok;
}

bool luaval_to_ccluavaluevector(lua_State* L, int lo, LuaValueArray* ret, const char* funcName)
{
    if (nullptr == L || nullptr == ret)
        return false;

    tolua_Error tolua_err;
    bool ok = true;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if COCOS2D_DEBUG >=1
        // luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }

    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        for (size_t i = 0; i < len; i++)
        {
            lua_pushnumber(L,i + 1);
            lua_gettable(L,lo);
            if (lua_isnil(L,-1))
            {
                lua_pop(L, 1);
                continue;
            }

            if(lua_istable(L, -1))
            {
                lua_pushnumber(L,1);
                lua_gettable(L,-2);
                if (lua_isnil(L, -1) )
                {
                    lua_pop(L,1);
                    LuaValueDict dictVal;
                    if (luaval_to_ccluavaluemap(L, lua_gettop(L), &dictVal))
                    {
                        ret->push_back(LuaValue::dictValue(dictVal));
                    }
                }
                else
                {
                    lua_pop(L,1);
                    LuaValueArray arrVal;
                    if(luaval_to_ccluavaluevector(L, lua_gettop(L), &arrVal))
                    {
                        ret->push_back(LuaValue::arrayValue(arrVal));
                    }
                }
            }
            else if(lua_type(L, -1) == LUA_TSTRING)
            {
                std::string stringValue = "";
                if(luaval_to_std_string(L, -1, &stringValue) )
                {
                    ret->push_back(LuaValue::stringValue(stringValue));
                }
            }
            else if(lua_type(L, -1) == LUA_TBOOLEAN)
            {
                bool boolVal = false;
                if (luaval_to_boolean(L, -1, &boolVal))
                {
                    ret->push_back(LuaValue::booleanValue(boolVal));
                }
            }
            else if(lua_type(L, -1) == LUA_TNUMBER)
            {
                ret->push_back(LuaValue::floatValue(tolua_tonumber(L, -1, 0)));
            }
            else
            {
                //                CCASSERT(false, "not supported type");
            }
            lua_pop(L, 1);
        }
    }

    return ok;
}

#if COCOS2D_VERSION <= 0x00030600
void std_map_string_string_to_luaval(lua_State* L, const std::map<std::string, std::string>& inValue) {
    if (nullptr == L) {
        return;
    }

    lua_newtable(L);

    for (std::map<std::string, std::string>::const_iterator iter = inValue.begin(); iter != inValue.end(); ++iter) {
        lua_pushstring(L, iter->first.c_str());
        lua_pushstring(L, iter->second.c_str());
        lua_rawset(L, -3);
    }
}

bool luaval_to_std_map_string_string(lua_State* L, int lo, std::map<std::string, std::string>* ret, const char* funcName) {
    if (nullptr == L || nullptr == ret || lua_gettop(L) < lo)
        return false;

    tolua_Error tolua_err;
    bool ok = true;
    if (!tolua_istable(L, lo, 0, &tolua_err)) {
        ok = false;
    }

    if (!ok)
        return ok;

    lua_pushnil(L);
    std::string key;
    std::string value;
    while (lua_next(L, lo) != 0) {
        if (lua_isstring(L, -2) && lua_isstring(L, -1)) {
            if (luaval_to_std_string(L, -2, &key) && luaval_to_std_string(L, -1, &value)) {
                (*ret)[key] = value;
            }
        } else {
            //CCASSERT(false, "string type is needed");
        }

        lua_pop(L, 1);
    }

    return ok;
}
#endif



bool luatable_to_map_string_string(lua_State* L, int lo, std::map<std::string,std::string>* ret, const char* funcName)
{
    if ( nullptr == L || nullptr == ret)
        return false;

    tolua_Error tolua_err;
    bool ok = true;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
        ok = false;
    }

    if (ok)
    {
        std::string stringKey = "";
        std::string stringValue = "";
        bool boolVal = false;
        std::map<std::string,std::string>& dict = *ret;
        lua_pushnil(L);                                             /* first key L: lotable ..... nil */
        while ( 0 != lua_next(L, lo ) )                             /* L: lotable ..... key value */
        {
            if (!lua_isstring(L, -2))
            {
                lua_pop(L, 1);                                      /* removes 'value'; keep 'key' for next iteration*/
                continue;
            }

            if(luaval_to_std_string(L, -2, &stringKey))
            {

                if(lua_istable(L, -1))
                {
                    // skip nested objects
                }
                else if(lua_type(L, -1) == LUA_TSTRING)
                {
                    if(luaval_to_std_string(L, -1, &stringValue))
                    {
                        dict[stringKey] = stringValue;
                    }
                }
                else if(lua_type(L, -1) == LUA_TBOOLEAN)
                {
                    if (luaval_to_boolean(L, -1, &boolVal))
                    {
                        dict[stringKey] = boolVal ? "true" : "false";
                    }
                }
                else if(lua_type(L, -1) == LUA_TNUMBER)
                {
                    char c[80];
                    snprintf( c, sizeof(c), "%f",tolua_tonumber(L, -1, 0) );
                    dict[stringKey] = std::string(c) ;
                }
            }

            lua_pop(L, 1);                                          /* L: lotable ..... key */
        }
    }

    return ok;
}




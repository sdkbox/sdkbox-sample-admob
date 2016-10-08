#ifndef __SDKBOX_LUA_HELPER_H__
#define __SDKBOX_LUA_HELPER_H__

#include "cocos2d.h"

#if COCOS2D_VERSION >= 0x00031100
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#else
#include "CCLuaEngine.h"
#include "tolua_fix.h"
#endif

#if COCOS2D_VERSION >= 0x00030000

#if COCOS2D_VERSION >= 0x00031100
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#else
#include "LuaBasicConversions.h"
#endif

#define LUAENGINE cocos2d::LuaEngine::getInstance()

#else

#define nullptr NULL

#define LuaValueDict CCLuaValueDict
#define LuaValueDictIterator CCLuaValueDictIterator
#define LuaValueArray CCLuaValueArray
#define LuaValue CCLuaValue
#define LuaEngine CCLuaEngine
#define LuaStack CCLuaStack
#define LUAENGINE cocos2d::LuaEngine::defaultEngine()
#define pushLuaValueDict pushCCLuaValueDict
#define pushLuaValueArray pushCCLuaValueArray
#define pushLuaValue pushCCLuaValue


extern "C" {
#include "lua.h"
#include "tolua++.h"
}
#include "tolua_fix.h"
#include "cocos2d.h"

using namespace cocos2d;

extern std::map<std::string, std::string>  g_luaType;
extern std::map<std::string, std::string>  g_typeCast;

#if COCOS2D_DEBUG >=1
void luaval_to_native_err(lua_State* L,const char* msg,tolua_Error* err, const char* funcName = "");
#endif

// to native

extern bool luaval_to_ulong(lua_State* L,int lo, unsigned long* outValue, const char* funcName="");

extern bool luaval_to_ushort(lua_State* L, int lo, unsigned short* outValue, const char* funcName = "");

extern bool luaval_to_int32(lua_State* L,int lo,int* outValue, const char* funcName = "");

extern bool luaval_to_uint32(lua_State* L, int lo, unsigned int* outValue, const char* funcName = "");

extern bool luaval_to_uint16(lua_State* L,int lo,uint16_t* outValue, const char* funcName = "");

extern bool luaval_to_boolean(lua_State* L,int lo,bool* outValue, const char* funcName = "");

extern bool luaval_to_number(lua_State* L,int lo,double* outValue, const char* funcName = "");

extern bool luaval_to_long_long(lua_State* L,int lo,long long* outValue, const char* funcName = "");

extern bool luaval_to_std_string(lua_State* L, int lo, std::string* outValue, const char* funcName = "");

extern bool luaval_to_long(lua_State* L,int lo, long* outValue, const char* funcName = "");

extern bool luaval_to_ssize(lua_State* L,int lo, ssize_t* outValue, const char* funcName = "");

bool luaval_to_std_vector_string(lua_State* L, int lo, std::vector<std::string>* ret, const char* funcName = "");

bool luaval_to_std_vector_int(lua_State* L, int lo, std::vector<int>* ret, const char* funcName = "");

extern bool luaval_to_std_vector_float(lua_State* L, int lo, std::vector<float>* ret, const char* funcName = "");

extern bool luaval_to_std_vector_ushort(lua_State* L, int lo, std::vector<unsigned short>* ret, const char* funcName = "");

void ccvector_std_string_to_luaval(lua_State* L, const std::vector<std::string>& inValue);

void ccvector_int_to_luaval(lua_State* L, const std::vector<int>& inValue);

void ccvector_float_to_luaval(lua_State* L, const std::vector<float>& inValue);

void ccvector_ushort_to_luaval(lua_State* L, const std::vector<unsigned short>& inValue);

#endif // COCOS2D_VERSION < 0x00030000

extern bool luaval_to_ccluavaluemap(lua_State* L, int lo, LuaValueDict* ret, const char* funcName = "");

extern bool luaval_to_ccluavaluevector(lua_State* L, int lo, LuaValueArray* ret, const char* funcName = "'");

#if COCOS2D_VERSION <= 0x00030600
extern void std_map_string_string_to_luaval(lua_State* L, const std::map<std::string, std::string>& inValue);
extern bool luaval_to_std_map_string_string(lua_State* L, int lo, std::map<std::string, std::string>* ret, const char* funcName);
#endif

bool luatable_to_map_string_string(lua_State* L, int lo, std::map<std::string,std::string>* ret, const char* funcName);

#endif //__SDKBOX_LUA_HELPER_H__

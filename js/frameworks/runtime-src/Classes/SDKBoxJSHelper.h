#ifndef __SDKBOX_JS_HELPER_H__
#define __SDKBOX_JS_HELPER_H__

#include "jsapi.h"
#include "jsfriendapi.h"
#include <map>
#include <vector>
#include <string>

#include "cocos2d.h"
#if (COCOS2D_VERSION >= 0x00031100)
#include "scripting/js-bindings/manual/js_manual_conversions.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "scripting/js-bindings/manual/ScriptingCore.h"
#else
#include "js_manual_conversions.h"
#include "cocos2d_specifics.hpp"
#include "ScriptingCore.h"
#endif

#ifndef SDKBOX_COCOS_JSB_VERSION
    #if defined(SDKBOX_COCOS_CREATOR)
        #define SDKBOX_COCOS_JSB_VERSION 2
    #elif COCOS2D_VERSION >= 0x00031000
        #define SDKBOX_COCOS_JSB_VERSION 2
    #else
        #define SDKBOX_COCOS_JSB_VERSION 1
    #endif
#endif

#if MOZJS_MAJOR_VERSION >= 31
typedef JS::HandleObject one_JSObject;
#else
typedef JSObject* one_JSObject;
#endif

#if COCOS2D_VERSION < 0x00030000
// wraps a function and "this" object
class JSFunctionWrapper
{
public:
    JSFunctionWrapper(JSContext* cx, JSObject *jsthis, jsval fval);
    ~JSFunctionWrapper();
private:
    JSContext *_cx;
    JSObject *_jsthis;
    jsval _fval;
};
#endif // JSFunctionWrapper

namespace sdkbox
{
    class JSListenerBase
    {
    public:
        JSListenerBase();
        virtual ~JSListenerBase();

        void setJSDelegate(JS::HandleValue func);
        JSObject* getJSDelegate();

    protected:
        JSObject* _JSDelegate;
        JSFunctionWrapper *_jsFuncWrapper;
    };

// Spidermonkey v186+
#if defined(MOZJS_MAJOR_VERSION) and MOZJS_MAJOR_VERSION >= 26
    bool js_to_number(JSContext *cx, JS::HandleValue v, double *dp);
    bool jsval_to_std_map_string_string(JSContext *cx, JS::HandleValue v, std::map<std::string,std::string> *ret);
    void getJsObjOrCreat(JSContext* cx, JS::HandleObject jsObj, const char* name, JS::RootedObject* retObj);
#else
    JSBool js_to_number(JSContext *cx, jsval v, double *dp);
    JSBool jsval_to_std_map_string_string(JSContext *cx, jsval v, std::map<std::string,std::string> *ret);
    jsval getJsObjOrCreat(JSContext* cx, JSObject* jsObj, const char* name, JSObject** retObj);
    jsval std_vector_string_to_jsval(JSContext* cx, const std::vector<std::string>& arr);
    JSBool jsval_to_std_vector_string(JSContext* cx, jsval v, std::vector<std::string>* ret);
#endif
    jsval std_map_string_int_to_jsval(JSContext* cx, const std::map<std::string, int>& v);
    jsval std_map_string_string_to_jsval(JSContext* cx, const std::map<std::string, std::string>& v);


////////////////////////////////////////////////////////////////////////////////
///                     SPIDER MONKEY UTILITIES  - START                     ///
////////////////////////////////////////////////////////////////////////////////

#ifndef __SPIDERMONKEY_UTILS__
#define __SPIDERMONKEY_UTILS__

    #if defined(MOZJS_MAJOR_VERSION)
        #if MOZJS_MAJOR_VERSION >= 33
            typedef JSObject JSOBJECT;

            #define JS_SET_PROPERTY(cx, jsobj, prop, pr) JS_SetProperty( cx, JS::RootedObject(cx,jsobj), prop, JS::RootedValue(cx,pr) )

        #else

            typedef JSObject JSOBJECT;

            #define JS_SET_PROPERTY(cx, jsobj, prop, pr) JS_SetProperty( cx, jsobj, prop, pr )

        #endif

        #define JS_INIT_CONTEXT_FOR_UPDATE(cx)                                          \
            JS::RootedObject obj(cx, ScriptingCore::getInstance()->getGlobalObject());  \
            JSAutoCompartment ac(cx, obj);

        typedef JS::RootedValue     JSPROPERTY_VALUE;
        typedef JS::RootedString    JSPROPERTY_STRING;
        typedef JS::RootedObject    JSPROPERTY_OBJECT;

        typedef bool                JS_BOOL;

        typedef JS::CallArgs        JS_FUNCTION_ARGS;
        #define JS_FUNCTION_GET_ARGS(argc,argv)         JS::CallArgsFromVp(argc, vp)
        #define JS_FUNCTION_ARGS_GET(args,index)        args.get(index)
        #define JS_FUNCTION_RETURN_UNDEFINED(cx,args)   args.rval().setUndefined()

    #elif defined(JS_VERSION)
        typedef JSObject            JSOBJECT;

        typedef jsval               JSPROPERTY_VALUE;
        typedef jsval               JSPROPERTY_STRING;
        typedef jsval               JSPROPERTY_OBJECT;

        typedef JSBool              JS_BOOL;

        #define JS_SET_PROPERTY(cx, jsobj, prop, pr) JS_SetProperty( cx, jsobj, prop, &pr )
        #define JS_INIT_CONTEXT_FOR_UPDATE(cx)

        typedef jsval*        JS_FUNCTION_ARGS;
        #define JS_FUNCTION_GET_ARGS(cx,argc)           JS_ARGV(cx, argv)
        #define JS_FUNCTION_ARGS_GET(args,index)        args[index]
        #define JS_FUNCTION_RETURN_UNDEFINED(cx,args)   JS_SET_RVAL(cx, args, JSVAL_VOID)

    #endif


    #if defined(MOZJS_MAJOR_VERSION)

        JSOBJECT* JS_NEW_OBJECT( JSContext* cs );

        template<typename T>
        bool JS_ARRAY_SET(JSContext* cx, JSOBJECT* array, uint32_t index, T pr);
        bool JS_ARRAY_SET(JSContext* cx, JSOBJECT* array, uint32_t index, JSOBJECT* v);

    #elif defined(JS_VERSION)

        template<typename T>
        bool JS_ARRAY_SET(JSContext* cx, JSOBJECT* array, uint32_t index, T pr);

        JSOBJECT* JS_NEW_OBJECT( JSContext* cs );

    #endif

    JSObject* make_array( JSContext* ctx, int size );
    jsval make_property( JSContext*ctx );

    JSOBJECT* JS_NEW_ARRAY( JSContext* cx, uint32_t size );
    JSOBJECT* JS_NEW_ARRAY( JSContext* cx );
    void addProperty( JSContext* cx, JSOBJECT* jsobj, const char* prop, const std::string& value );
    void addProperty( JSContext* cx, JSOBJECT* jsobj, const char* prop, const char* value );
    void addProperty( JSContext* cx, JSOBJECT* jsobj, const char* prop, bool value );
    void addProperty( JSContext* cx, JSOBJECT* jsobj, const char* prop, int value );
    void addProperty( JSContext* cx, JSOBJECT* jsobj, const char* prop, JSOBJECT* value );

#endif
}
////////////////////////////////////////////////////////////////////////////////
///                      SPIDER MONKEY UTILITIES  - END                      ///
////////////////////////////////////////////////////////////////////////////////

#endif //__SDKBOX_JS_HELPER_H__

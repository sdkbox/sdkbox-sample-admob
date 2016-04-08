#include "PluginAdMobJSHelper.h"
#include "cocos2d_specifics.hpp"
#include "PluginAdMob/PluginAdMob.h"
#include "SDKBoxJSHelper.h"

#include "js_manual_conversions.h"

extern JSObject* jsb_sdkbox_PluginAdMob_prototype;
static JSContext* s_cx = nullptr;

class AdMobCallbackJS: public cocos2d::CCObject {
public:
    AdMobCallbackJS();
    void schedule();
    void notityJs(float dt);

    std::string _name;

    jsval _paramVal[2];
    int _paramLen;
};

class AdMobListenerJS : public sdkbox::AdMobListener {
private:
    JSObject* _JSDelegate;
public:
    void setJSDelegate(JSObject* delegate) {
        _JSDelegate = delegate;
    }

    JSObject* getJSDelegate() {
        return _JSDelegate;
    }

    void adViewDidReceiveAd(const std::string &name) {
        JSContext* cx = s_cx;
        AdMobCallbackJS* cb = new AdMobCallbackJS();
        cb->_name = "adViewDidReceiveAd";
        cb->_paramVal[0] = std_string_to_jsval(cx, name);
        cb->_paramLen = 1;
        cb->schedule();
    }
    void adViewDidFailToReceiveAdWithError(const std::string &name, const std::string &msg) {
        JSContext* cx = s_cx;
        AdMobCallbackJS* cb = new AdMobCallbackJS();
        cb->_name = "adViewDidFailToReceiveAdWithError";
        cb->_paramVal[0] = std_string_to_jsval(cx, name);
        cb->_paramVal[1] = std_string_to_jsval(cx, msg);
        cb->_paramLen = 2;
        cb->schedule();
    }
    void adViewWillPresentScreen(const std::string &name) {
        JSContext* cx = s_cx;
        AdMobCallbackJS* cb = new AdMobCallbackJS();
        cb->_name = "adViewWillPresentScreen";
        cb->_paramVal[0] = std_string_to_jsval(cx, name);
        cb->_paramLen = 1;
        cb->schedule();
    }
    void adViewDidDismissScreen(const std::string &name) {
        JSContext* cx = s_cx;
        AdMobCallbackJS* cb = new AdMobCallbackJS();
        cb->_name = "adViewDidDismissScreen";
        cb->_paramVal[0] = std_string_to_jsval(cx, name);
        cb->_paramLen = 1;
        cb->schedule();
    }
    void adViewWillDismissScreen(const std::string &name) {
        JSContext* cx = s_cx;
        AdMobCallbackJS* cb = new AdMobCallbackJS();
        cb->_name = "adViewWillDismissScreen";
        cb->_paramVal[0] = std_string_to_jsval(cx, name);
        cb->_paramLen = 1;
        cb->schedule();
    }
    void adViewWillLeaveApplication(const std::string &name) {
        JSContext* cx = s_cx;
        AdMobCallbackJS* cb = new AdMobCallbackJS();
        cb->_name = "adViewWillLeaveApplication";
        cb->_paramVal[0] = std_string_to_jsval(cx, name);
        cb->_paramLen = 1;
        cb->schedule();
    }

    void invokeJS(const char* func, jsval* pVals, int valueSize) {
        if (!s_cx) {
            return;
        }
        JSContext* cx = s_cx;
        const char* func_name = func;
        JS::RootedObject obj(cx, _JSDelegate);
        JSAutoCompartment ac(cx, obj);

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
        bool hasAction;
        JS::RootedValue retval(cx);
        JS::RootedValue func_handle(cx);
#else
        bool hasAction;
        jsval retval;
        JS::RootedValue func_handle(cx);
#endif
#elif defined(JS_VERSION)
        JSBool hasAction;
        jsval retval;
        jsval func_handle;
#endif

        if (JS_HasProperty(cx, obj, func_name, &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, func_name, &func_handle)) {
                return;
            }
            if(func_handle == JSVAL_VOID) {
                return;
            }

#if MOZJS_MAJOR_VERSION >= 31
            if (0 == valueSize) {
                JS_CallFunctionName(cx, obj, func_name, JS::HandleValueArray::empty(), &retval);
            } else {
                JS_CallFunctionName(cx, obj, func_name, JS::HandleValueArray::fromMarkedLocation(valueSize, pVals), &retval);
            }
#else
            if (0 == valueSize) {
                JS_CallFunctionName(cx, obj, func_name, 0, nullptr, &retval);
            } else {
                JS_CallFunctionName(cx, obj, func_name, valueSize, pVals, &retval);
            }
#endif
        }
    }

};


AdMobCallbackJS::AdMobCallbackJS():
_paramLen(0) {
}

void AdMobCallbackJS::schedule() {
    retain();
    cocos2d::CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(AdMobCallbackJS::notityJs), this, 0, false);
    autorelease();
}

void AdMobCallbackJS::notityJs(float dt) {
    sdkbox::AdMobListener* lis = sdkbox::PluginAdMob::getListener();
    AdMobListenerJS* l = dynamic_cast<AdMobListenerJS*>(lis);
    if (l) {
        l->invokeJS(_name.c_str(), _paramVal, _paramLen);
    }
    cocos2d::CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(this);
    release();
}


#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
bool js_PluginAdMobJS_PluginAdMob_setListener(JSContext *cx, uint32_t argc, jsval *vp)
#else
bool js_PluginAdMobJS_PluginAdMob_setListener(JSContext *cx, uint32_t argc, jsval *vp)
#endif
#elif defined(JS_VERSION)
JSBool js_PluginAdMobJS_PluginAdMob_setListener(JSContext *cx, uint32_t argc, jsval *vp)
#endif
{
    s_cx = cx;
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    if (argc == 1) {

        if (!args.get(0).isObject())
        {
            ok = false;
        }
        JSObject *tmpObj = args.get(0).toObjectOrNull();

        JSB_PRECONDITION2(ok, cx, false, "js_PluginAdMobJS_PluginAdMob_setIAPListener : Error processing arguments");
        AdMobListenerJS* wrapper = new AdMobListenerJS();
        wrapper->setJSDelegate(tmpObj);
        sdkbox::PluginAdMob::setListener(wrapper);

        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginAdMobJS_PluginAdMob_setIAPListener : wrong number of arguments");
    return false;
}


#if defined(MOZJS_MAJOR_VERSION) and MOZJS_MAJOR_VERSION >= 26
void admob_set_constants(JSContext* cx, const JS::RootedObject& obj, const std::string& name, const std::map<std::string, int>& params)
#else
void admob_set_constants(JSContext* cx, JSObject* obj, const std::string& name, const std::map<std::string, int>& params)
#endif
{
    jsval val = sdkbox::std_map_string_int_to_jsval(cx, params);

    JS::RootedValue rv(cx);
    rv = val;
#if defined(MOZJS_MAJOR_VERSION) and MOZJS_MAJOR_VERSION >= 26
    JS_SetProperty(cx, obj, name.c_str(), rv);
#else
    JS_SetProperty(cx, obj, name.c_str(), rv.address());
#endif
}

#if defined(MOZJS_MAJOR_VERSION) and MOZJS_MAJOR_VERSION >= 26
void admob_register_constants(JSContext* cx, const JS::RootedObject& obj)
#else
void admob_register_constants(JSContext* cx, JSObject* obj)
#endif
{
    // std::map<std::string, int> enums;
    // enums.clear();
    // enums.insert(std::make_pair("kIMSDKGenderMale", 1));
    // enums.insert(std::make_pair("kIMSDKGenderFemale", 2));
    // admob_set_constants(cx, obj, "SBIMSDKGender", enums);
}

#define REGISTE_ADMOB_FUNCTIONS \
JS_DefineFunction(cx, pluginObj, "setListener", js_PluginAdMobJS_PluginAdMob_setListener, 1, JSPROP_READONLY | JSPROP_PERMANENT); \
admob_register_constants(cx, pluginObj);

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void register_all_PluginAdMobJS_helper(JSContext* cx, JS::HandleObject global) {
    JS::RootedObject pluginObj(cx);
    sdkbox::getJsObjOrCreat(cx, global, "sdkbox.PluginAdMob", &pluginObj);

    REGISTE_ADMOB_FUNCTIONS
}
#else
void register_all_PluginAdMobJS_helper(JSContext* cx, JSObject* global) {
    JS::RootedObject pluginObj(cx);
    sdkbox::getJsObjOrCreat(cx, JS::RootedObject(cx, global), "sdkbox.PluginAdMob", &pluginObj);

    REGISTE_ADMOB_FUNCTIONS
}
#endif
#elif defined(JS_VERSION)
void register_all_PluginAdMobJS_helper(JSContext* cx, JSObject* global) {
    jsval pluginVal;
    JSObject* pluginObj;
    pluginVal = sdkbox::getJsObjOrCreat(cx, global, "sdkbox.PluginAdMob", &pluginObj);

    REGISTE_ADMOB_FUNCTIONS
}
#endif

#ifndef __PluginAdMobJS_h__
#define __PluginAdMobJS_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_sdkbox_PluginAdMob_class;
extern JSObject *jsb_sdkbox_PluginAdMob_prototype;

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginAdMobJS_PluginAdMob(JSContext *cx, JS::HandleObject global);
void register_all_PluginAdMobJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginAdMobJS_PluginAdMob(JSContext *cx, JSObject* global);
void register_all_PluginAdMobJS(JSContext* cx, JSObject* obj);
#endif

bool js_PluginAdMobJS_PluginAdMob_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_PluginAdMobJS_PluginAdMob_finalize(JSContext *cx, JSObject *obj);
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginAdMobJS_PluginAdMob_getCurrBannerHeight(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginAdMobJS_PluginAdMob_getCurrBannerHeight(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginAdMobJS_PluginAdMob_getCurrBannerHeightInPixel(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginAdMobJS_PluginAdMob_getCurrBannerHeightInPixel(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginAdMobJS_PluginAdMob_hide(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginAdMobJS_PluginAdMob_hide(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginAdMobJS_PluginAdMob_setTestDevices(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginAdMobJS_PluginAdMob_setTestDevices(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginAdMobJS_PluginAdMob_show(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginAdMobJS_PluginAdMob_show(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginAdMobJS_PluginAdMob_getCurrBannerWidthInPixel(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginAdMobJS_PluginAdMob_getCurrBannerWidthInPixel(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginAdMobJS_PluginAdMob_cache(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginAdMobJS_PluginAdMob_cache(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginAdMobJS_PluginAdMob_getCurrBannerWidth(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginAdMobJS_PluginAdMob_getCurrBannerWidth(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginAdMobJS_PluginAdMob_init(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginAdMobJS_PluginAdMob_init(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginAdMobJS_PluginAdMob_getVersion(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginAdMobJS_PluginAdMob_getVersion(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginAdMobJS_PluginAdMob_isAvailable(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginAdMobJS_PluginAdMob_isAvailable(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#endif


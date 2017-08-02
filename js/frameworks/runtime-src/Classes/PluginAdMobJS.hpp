#ifndef __PluginAdMobJS_h__
#define __PluginAdMobJS_h__

#include "jsapi.h"
#include "jsfriendapi.h"


#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginAdMobJS_PluginAdMob(JSContext *cx, JS::HandleObject global);
void register_all_PluginAdMobJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginAdMobJS_PluginAdMob(JSContext *cx, JSObject* global);
void register_all_PluginAdMobJS(JSContext* cx, JSObject* obj);
#endif
#endif


/****************************************************************************

 Copyright (c) 2014-2016 SDKBOX Inc

 ****************************************************************************/

#ifndef _PLUGIN_ADMOB_WRAPPER_H_
#define _PLUGIN_ADMOB_WRAPPER_H_

#include "PluginAdMob.h"
#include "json98.h"
#include "CocosMacros.h"
#include <map>

#define TAG "AdMob"
#define VERSION "8.4.0"
#define ADMOB_ANDROID_VERSION "8.4.0"

namespace sdkbox {

#define CHECK_ADMOB_LISTENER if (sdkbox::PluginAdMob::getListener() == nullptr) return;

class AdMobWrapper {

public:
    struct ad_info_t {
        std::string name;
        std::string ID;
        std::string type;
        std::string alignment;
        int width;
        int height;
        bool tag_for_child_directed_treatment;
    };

    static AdMobWrapper* getInstance();

    virtual bool init() = 0;
    virtual void setListener(AdMobListener* listener) = 0;
    virtual AdMobListener* getListener() = 0;
    virtual void removeListener() = 0;
    virtual std::string getVersion() const = 0;

    virtual void setTestDevices(const std::string &devices) = 0;

    virtual void cache(const std::string &name) = 0;
    virtual void show(const std::string &name) = 0;
    virtual void hide(const std::string &name) = 0;
    virtual bool isAvailable(const std::string &name) = 0;
    virtual int getCurrBannerWidth() = 0;
    virtual int getCurrBannerHeight() = 0;
    virtual int getCurrBannerWidthInPixel() = 0;
    virtual int getCurrBannerHeightInPixel() = 0;


    virtual void showDefault() = 0;

    //
    virtual void onAdViewDidReceiveAd(const std::string &name) = 0;
    virtual void onAdViewDidFailToReceiveAdWithError(const std::string &name, const std::string &msg) = 0;
    virtual void onAdViewWillPresentScreen(const std::string &name) = 0;
    virtual void onAdViewDidDismissScreen(const std::string &name) = 0;
    virtual void onAdViewWillDismissScreen(const std::string &name) = 0;
    virtual void onAdViewWillLeaveApplication(const std::string &name) = 0;
};

class AdMobWrapperEnabled : public AdMobWrapper {

public:
    AdMobWrapperEnabled();

    bool init();
    void setListener(AdMobListener* listener);
    AdMobListener* getListener();
    void removeListener();
    std::string getVersion() const;

    void setTestDevices(const std::string &devices);

    void cache(const std::string &name);
    void show(const std::string &name);
    void hide(const std::string &name);
    bool isAvailable(const std::string &name);
    int getCurrBannerWidth();
    int getCurrBannerHeight();
    int getCurrBannerWidthInPixel();
    int getCurrBannerHeightInPixel();

    void showDefault();

    //
    void onAdViewDidReceiveAd(const std::string &name);
    void onAdViewDidFailToReceiveAdWithError(const std::string &name, const std::string &msg);
    void onAdViewWillPresentScreen(const std::string &name);
    void onAdViewDidDismissScreen(const std::string &name);
    void onAdViewWillDismissScreen(const std::string &name);
    void onAdViewWillLeaveApplication(const std::string &name);
protected:
    bool nativeInit(const Json& config);
    std::string nativeSDKVersion() const;

    AdMobListener* _listener;
    std::map<std::string, AdMobWrapper::ad_info_t> _ads;
};

class AdMobWrapperDisabled : public AdMobWrapper {

public:
    AdMobWrapperDisabled() {}

    bool init() { return false; }
    void setListener(AdMobListener* listener) {}
    AdMobListener* getListener() { return NULL; }
    void removeListener() {}
    std::string getVersion() const { return ""; }

    void setTestDevices(const std::string &devices) {}

    void cache(const std::string &name) {}
    void show(const std::string &name) {}
    void hide(const std::string &name) {}
    bool isAvailable(const std::string &name) { return false; }
    int getCurrBannerWidth() { return -1; }
    int getCurrBannerHeight() { return -1; }
    int getCurrBannerWidthInPixel() { return -1; }
    int getCurrBannerHeightInPixel() { return -1; }

    void showDefault() {}

    //
    void onAdViewDidReceiveAd(const std::string &name) {}
    void onAdViewDidFailToReceiveAdWithError(const std::string &name, const std::string &msg) {}
    void onAdViewWillPresentScreen(const std::string &name) {}
    void onAdViewDidDismissScreen(const std::string &name) {}
    void onAdViewWillDismissScreen(const std::string &name) {}
    void onAdViewWillLeaveApplication(const std::string &name) {}
};


}

#endif

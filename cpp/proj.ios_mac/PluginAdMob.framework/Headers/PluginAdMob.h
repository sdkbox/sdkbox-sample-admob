/****************************************************************************

 Copyright (c) 2014-2016 SDKBOX Inc

 ****************************************************************************/

#ifndef _PLUGIN_ADMOB_H_
#define _PLUGIN_ADMOB_H_

#include <string>

namespace sdkbox {

    class AdMobListener;
    class PluginAdMob {
    public:

        // enum SBIMSDKGender {
        //     kIMSDKGenderMale = 1,
        //     kIMSDKGenderFemale
        // };

        /**
         *  initialize the plugin instance.
         */
        static bool init();

        /**
         * Set listener to listen for admob events
         */
        static void setListener(AdMobListener* listener);

        /**
         * Get the listener
         */
        static AdMobListener* getListener();

        /**
         * Remove the listener, and can't listen to events anymore
         */
        static void removeListener();

        /**
         * Use this to get the version of the SDK.
         * @return The version of the SDK.
         */
        static std::string getVersion();

        /**
         * Set test devices
         */
        static void setTestDevices(const std::string &devices);
        
        /**
         * Cache ad with @name
         */
        static void cache(const std::string &name);
        
        /**
         * show ad with @name
         */
        static void show(const std::string &name);
        
        /**
         * hide ad with @name
         *
         * interstitial does not support hide
         */
        static void hide(const std::string &name);
        
        /**
         * check whether ad available with @name
         */
        static bool isAvailable(const std::string &name);
        
        /**
         * get width of current banner
         *
         * @return: -1 means current banner is not available
         */
        static int getCurrBannerWidth(const std::string &name = "");

        /**
         * get height of current banner
         *
         * @return: -1 means current banner is not available
         */
        static int getCurrBannerHeight(const std::string &name = "");

        /**
         * get width of current banner in pixel
         *
         * @return -1 means current banner is not available
         */
        static int getCurrBannerWidthInPixel(const std::string &name = "");

        /**
         * get height of current banner in pixel
         *
         * @return: -1 means current banner is not available
         */
        static int getCurrBannerHeightInPixel(const std::string &name = "");
    };
    
    class AdMobListener {
    public:
        virtual void adViewDidReceiveAd(const std::string &name) {}
        virtual void adViewDidFailToReceiveAdWithError(const std::string &name, const std::string &msg) {}
        virtual void adViewWillPresentScreen(const std::string &name) {}
        virtual void adViewDidDismissScreen(const std::string &name) {}
        virtual void adViewWillDismissScreen(const std::string &name) {}
        virtual void adViewWillLeaveApplication(const std::string &name) {}
        virtual void reward(const std::string &name, const std::string &currency, double amount) {}
    };
}

#endif

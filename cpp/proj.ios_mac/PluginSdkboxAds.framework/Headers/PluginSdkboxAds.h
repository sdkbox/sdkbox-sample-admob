/****************************************************************************

 Copyright (c) 2014-2015 Chukong Technologies

 ****************************************************************************/

#ifndef _PLUGIN_SDKBOXADS_H_
#define _PLUGIN_SDKBOXADS_H_


#include <vector>
#include <string>
#include <map>
#include <sdkbox/Sdkbox.h>

namespace sdkbox {

    typedef std::map<std::string,std::string> AdUnitParams;

    class PluginSdkboxAdsListener {
    public:

        /**
         * This method notifies back with the AdUnit identifier, the Ad name it tried to play,
         * and an enum type of the action it is communicating about.
         * The Action type is the following enum:
         *
         * <code>
         *  enum AdActionType {
         *      LOADED=0,               // content loaded
         *      LOAD_FAILED,            // content failed to load
         *
         *      CLICKED,                // clicked on content
         *
         *      REWARD_STARTED,     // reward started
         *      REWARD_ENDED,           // reward achieved
         *      REWARD_CANCELED,        // reward aborted
         *
         *      AD_STARTED,             // start showing
         *      AD_CANCELED,            // start showing.
         *      AD_ENDED,               // content shown
         *
         *      ADACTIONTYPE_UNKNOWN    // mostly on error situations.
         *  };
         *  </code>
         *
         *  Not all AdUnits will expose all types of events.
         *  For example, Chartboost notifies CLICKED action, but AdColony does not.
         *  Each AdUnit’s documentation will reflect what events will notify.
         */
        virtual void onAdAction( const std::string& ad_unit_id, const std::string& zone, sdkbox::AdActionType action_type) = 0;

        /**
         * This method will be called for REWARDED ads.
         * Some AdUnits offer finer control on the reward lifecycle, like whether it was cancelled,
         * or the amount of elements earned, while others don't.
         */
        virtual void onRewardAction( const std::string& ad_unit_id, const std::string& zone_id, float reward_amount, bool reward_succeed) = 0;
    };

    class PluginSdkboxAds {

    private:

        static PluginSdkboxAdsListener * _listener;

    public:

        /**
         * Initialize the plugin instance. 
         * The plugin initializes from the sdkbox_config.json file and reads configuration of the form:
         *
         *  <code>
         *    "SdkboxAds": {
         *        "units": [ "AdColony", "Fyber" ],
         *        "placements": [ {} ]
         *    }
         *  </code>
         *
         * The "units" array references other plugins' configuration. Sdkboxads mediates between other plugins
         * and/or simplifies interaction with them.
         * The "placements" block will be of the form:
         *
         *  <code>
         *     {
         *          “id” : “placement_id”,
         *          "strategy" : "round-robin", // only value by now.
         *          “units” : [
         *              <UnitDefinition>
         *          ]
         *      }
         *  </code>
         *
         * and each UnitDefinition as:
         *
         *  <code>
         *      {
         *          “Unit” : result_of_AdUnit.getId(),
         *          “name” : <a zone, place, location, existing in a Plugin's config>,
         *          “params” : json_object
         *      }
         *  </code>
         *
         * For a sample Sdkboxads config, check the example at Sdkbox github public repository.
         * The "params" configuration block will allow to pass in specific information to play ads
         * like location, position, etc.
         *
         * Check each AdUnit's documentation to find specifics on its configuration.
         */ 
        static void init();

        /**
         * Set Sdkboxads' plugin listener.
         * This listener will expose for each registered AdUnits, events related to Ads and Rewards.
         * In SdkboxAds, an Ad refers generally to VIDEO, INTERSTITIAL and BANNER.
         * Note that some ad units may have only Ads.
         */
        static void setListener(sdkbox::PluginSdkboxAdsListener *listener);

        /**
         * Retrieve plugin's listener.
         */ 
        static PluginSdkboxAdsListener * getListener();

        /**
         * Play an Ad identified by its zone/location/place with optional parameters.
         * AdUnits like Fyber which don't have zones, will use common placeholders like "INTERSTITIAL" or "REWARDED".
         * Some AdUnits may require extra information to play an Ad, and should use the params for that purpose.
         * You should refer to the documentation of each specific AdUnit about what parameters will accept.
         * 
         * The ad will be played for a specific AdUnit based on its identifier. The identifiers are the
         * values in the "units" node of the sdkbox_config.json file.
         * For example: "AdColony" or "Fyber".
         */
        static void playAd(const std::string& ad_unit, const std::string& zone_place_location, const AdUnitParams& params );
        static void playAd(const std::string& ad_unit, const std::string& zone_place_location );


        /**
         * Like the 3 parameter playAd method, this one plays an Ad for the default AdUnit.
         * Currently the default AdUnit is the first defined one in the sdkbox_config.json file.
         */
        static void playAd(const std::string&, const AdUnitParams& params );
        static void playAd(const std::string& );

        /**
         * Play a default Ad with the default AdUnit.
         * Each AdUnit knows how to play an Ad by default.
         * For example, AdColony will play the first video zone, or the first Reward if there's no one.
         */
        static void playAd();
        
        /**
         * A placement is a collection of mediated AdUnits.
         * When you want to invoke a placement, just call this method.
         * If the placement does not exist, the call will just be ignored.
         * A placement will take care of AdUnit’s cache control, so if the current AdUnit has no
         * cached content, or the AdUnit fails to load an ad, the next adUnit will be used.
         *
         * The placement will cycle throughout all the AdUnits it references, in a round robin fashion.
         * In the short term, new placement strategies will be added.
         */
        static void placement(const std::string& placement);

        /**
         * Manage cache control policies.
         * Not all AdUnits expose cache control while some others expose fine-grained cache control.
         * For example Chartboost offers specific cache control for each location, as well as
         * general Ads cache control.
         *
         * This method interfaces with the AdUnit’s cache mechanism. If no cache control is exposed
         * for a given AdUnit, the call will silently be ignored.
         *
         * Each AdUnit will document what valid values to pass to the cacheOpts parameter.
         * E.g. for Chartboost, these are valid values:
         *
         * cacheOpts for Chartboost:
         *
         *      element : bool
         *          Element corresponds to an identifiable CBLocation (ChartBoost)
         *
         *      e.g:
         *
         *  <code>
         *      {
         *          "Default": true, // a configuration location
         *          "Level Complete": true, // a configuration location
         *          "ADS": true // a general placeholder chartboost specific
         *      }
         *  </code>
         */
        static void cacheControl( const std::string& ad_unit, const std::map<std::string, std::string>& cacheOpts );
        
        /**
         * check if placement available
         */
        static bool isAvailable( const std::string& placement );

        /**
         * hide placement
         */
        static void hide(const std::string& placement);
        static void hideAd(const std::string& ad_unit, const std::string& zone_place_location );

    };

}

#endif

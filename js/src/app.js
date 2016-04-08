
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        cc.log("Sample Startup")

        this.createTestMenu();

        var winsize = cc.winSize;

        var logo = new cc.Sprite("res/Logo.png");
        var logoSize = logo.getContentSize();
        logo.x = logoSize.width / 2;
        logo.y = winsize.height - logoSize.height / 2;
        this.addChild(logo);

        var quit = new cc.MenuItemLabel(new cc.LabelTTF("QUIT", "sans", 32), function() {
            cc.log("QUIT");
        });
        var menu = new cc.Menu(quit);
        var size = quit.getContentSize();
        menu.x = winsize.width - size.width / 2 - 16;
        menu.y = size.height / 2 + 16;
        this.addChild(menu);

        return true;
    },

    createTestMenu:function() {
        var self = this;
        var size = cc.winSize;

        var coinsLabel = cc.Label.createWithSystemFont("Hello Js", "Arial", 32);
        coinsLabel.setPosition(size.width/2, 80);
        self.addChild(coinsLabel);
        self.coinsLabel = coinsLabel;

        cc.MenuItemFont.setFontName('arial');
        cc.MenuItemFont.setFontSize(32);


        self.kHomeBanner = "home";
        self.kGameOverAd = "gameover";
        printf = console.log

        var menu = new cc.Menu(
            // banner
            new cc.MenuItemFont("load banner", function () {
                sdkbox.PluginAdMob.cache(self.kHomeBanner);
            }, this),
            new cc.MenuItemFont("show banner", function () {
                sdkbox.PluginAdMob.show(self.kHomeBanner);
            }, this),
            new cc.MenuItemFont("hide banner", function () {
                sdkbox.PluginAdMob.hide(self.kHomeBanner);
            }, this),
            new cc.MenuItemFont("is banner available", function () {
                var yes = sdkbox.PluginAdMob.isAvailable(self.kHomeBanner);
                self.showText("is {0} is available {1}".format(self.kHomeBanner, yes));
            }, this),

            // interstitial
            new cc.MenuItemFont("load interstitial", function () {
                sdkbox.PluginAdMob.cache(self.kGameOverAd);
            }, this),
            new cc.MenuItemFont("show interstitial", function () {
                sdkbox.PluginAdMob.show(self.kGameOverAd);
            }, this),
            new cc.MenuItemFont("is interstitial available", function () {
                var yes = sdkbox.PluginAdMob.isAvailable(self.kGameOverAd);
                self.showText("is {0} is available {1}".format(self.kGameOverAd, yes));
            }, this)
            );
        menu.setPosition(size.width/2, size.height/2);
        menu.alignItemsVerticallyWithPadding(20);
        self.addChild(menu);

        var initSDK = function() {
            if ("undefined" == typeof(sdkbox)) {
                console.log("sdkbox is not exist")
                return
            }

            if ("undefined" != typeof(sdkbox.PluginAdMob)) {
                var plugin = sdkbox.PluginAdMob
                plugin.setListener({
                    adViewDidReceiveAd: function(name) {
                        self.showText('adViewDidReceiveAd name='+name);
                    },
                    adViewDidFailToReceiveAdWithError: function(name, msg) {
                        self.showText('adViewDidFailToReceiveAdWithError name={0} msg={1}'.format(name, msg));
                    },
                    adViewWillPresentScreen: function(name) {
                        self.showText('adViewWillPresentScreen name='+name);
                    },
                    adViewDidDismissScreen: function(name) {
                        self.showText('adViewDidDismissScreen name='+name);
                    },
                    adViewWillDismissScreen: function(name) {
                        self.showText('adViewWillDismissScreen='+name);
                    },
                    adViewWillLeaveApplication: function(name) {
                        self.showText('adViewWillLeaveApplication='+name);
                    }
                });
                plugin.init();

                // just for test
                if ("undefined" != typeof(plugin.deviceid) && plugin.deviceid.length > 0) {
                    console.log(">>>>{0}".format(plugin.deviceid));
                    plugin.setTestDevices(plugin.deviceid);
                }

            } else {
                printf("no plugin init")
            }
        }

        initSDK();

        var showText = function(msg) {
            printf(msg);
            self.coinsLabel.setString(msg);
        }
        self.showText = showText;
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});


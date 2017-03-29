
local MainScene = class("MainScene", cc.load("mvc").ViewBase)

function MainScene:onCreate()
    print("Sample Startup")

    local label = cc.Label:createWithSystemFont("QUIT", "sans", 32)
    local quit = cc.MenuItemLabel:create(label)
    quit:onClicked(function()
        os.exit(0)
    end)
    local size = label:getContentSize()
    local menu = cc.Menu:create(quit)
    menu:setPosition(display.right - size.width / 2 - 16, display.bottom + size.height / 2 + 16)
    self:addChild(menu)

    self:setupTestMenu()
end

function MainScene:setupTestMenu()
    self.status =
    cc.Label:createWithSystemFont("Hello Lua", "Arial", 32)
            :move(display.cx, 100)
            :addTo(self)
    self.status:setColor(cc.c3b(255, 0, 0))
    local showText = function(msg)
        printf(msg)
        self.status:setString(msg)
    end

    self.kHomeBanner = "home"
    self.kGameOverAd = "gameover"
    self.kRewardVideoAd = "rewarded"

    cc.MenuItemFont:setFontName("Arial")
    cc.Menu:create(
                   cc.MenuItemFont:create("load banner"):onClicked(function()
                        sdkbox.PluginAdMob:cache(self.kHomeBanner)
                    end),
                   cc.MenuItemFont:create("show banner"):onClicked(function()
                        sdkbox.PluginAdMob:show(self.kHomeBanner)
                    end),
                   cc.MenuItemFont:create("hide banner"):onClicked(function()
                        sdkbox.PluginAdMob:hide(self.kHomeBanner)
                    end),
                   cc.MenuItemFont:create("is banner available"):onClicked(function()
                        local yes = sdkbox.PluginAdMob:isAvailable(self.kHomeBanner) and "yes" or "no"
                        showText("is " .. self.kHomeBanner .. " available " .. yes)
                    end),

                   cc.MenuItemFont:create("load interstitial"):onClicked(function()
                        sdkbox.PluginAdMob:cache(self.kGameOverAd)
                    end),
                   cc.MenuItemFont:create("show interstitial"):onClicked(function()
                        sdkbox.PluginAdMob:show(self.kGameOverAd)
                    end),
                   cc.MenuItemFont:create("is interstitial available"):onClicked(function()
                        local yes = sdkbox.PluginAdMob:isAvailable(self.kGameOverAd) and "yes" or "no"
                        showText("is " .. self.kGameOverAd .. " available " .. yes)
                    end),
                   cc.MenuItemFont:create("load rewarded video"):onClicked(function (  )
                       sdkbox.PluginAdMob:cache(self.kRewardVideoAd)
                   end),
                   cc.MenuItemFont:create("show rewarded video"):onClicked(function (  )
                       sdkbox.PluginAdMob:show(self.kRewardVideoAd)
                   end)
                   )
        :move(display.cx, display.cy)
        :addTo(self)
        :alignItemsVerticallyWithPadding(20)


    require('cocos.cocos2d.json')
    local plugin = sdkbox.PluginAdMob
    plugin:setListener(function(args)
        local event = args.event
        dump(args, "admob listener info:")
        showText(json.encode(args))
        if event == "adViewDidReceiveAd" and args.name == self.kHomeBanner then
           plugin:show(self.kHomeBanner)
        elseif event == "adViewDidDismissScreen" then
            plugin:cache(args.name)
       end
    end)
    plugin:init()

    -- AdMobTestDeviceId comes from c++
    if AdMobTestDeviceId then
        print("the admob test device id is:", AdMobTestDeviceId)
        plugin:setTestDevices(AdMobTestDeviceId)
    end
end

return MainScene

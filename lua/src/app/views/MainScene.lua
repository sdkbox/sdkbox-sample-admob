
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
    local label1 = cc.Label:createWithSystemFont("Test Item 1", "sans", 28)
    local item1 = cc.MenuItemLabel:create(label1)
    item1:onClicked(function()
        print("Test Item 1")
    end)

    local label2 = cc.Label:createWithSystemFont("Test Item 2", "sans", 28)
    local item2 = cc.MenuItemLabel:create(label2)
    item2:onClicked(function()
        print("Test Item 2")
    end)

    local label3 = cc.Label:createWithSystemFont("Test Item 3", "sans", 28)
    local item3 = cc.MenuItemLabel:create(label3)
    item3:onClicked(function()
        print("Test Item 3")
    end)

    local menu = cc.Menu:create(item1, item2, item3)
    menu:alignItemsVerticallyWithPadding(24)
    self:addChild(menu)
end

return MainScene

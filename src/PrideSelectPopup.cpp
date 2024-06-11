#include "PrideSelectPopup.hpp"
#include <new>

#include "PrideManager.hpp"

using namespace geode::prelude;

PrideSelectPopup* PrideSelectPopup::create(const Callback& callback) {
    auto ret = new (std::nothrow) PrideSelectPopup();

    if (ret && ret->init(callback)) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}

bool PrideSelectPopup::init(const Callback& callback) {
    if (!FLAlertLayer::init(150)) {
        return false;
    }

    m_callback = callback;

    setupBase();
    setupButtonMenu();
    setupPage();
    setupPreview();

    // Update initial selection.
    auto PM = PrideManager::sharedManager();
    select(PM->getStreakID(), false);

    return true;
}

void PrideSelectPopup::keyBackClicked() {
    onClose(nullptr);
}

void PrideSelectPopup::setupBase() {
    auto director = CCDirector::sharedDirector();
    auto winSize = director->getWinSize();

    const auto size = CCSizeMake(300.0f, 250.0f);

    // Setup background.
    m_background = CCScale9Sprite::create("GJ_square01.png");
    m_background->setContentSize(size);
    m_background->setPosition(winSize / 2.0f);
    m_mainLayer->addChild(m_background, -2);

    // Setup button menu.
    m_buttonMenu = CCMenu::create();
    m_buttonMenu->ignoreAnchorPointForPosition(false);
    m_buttonMenu->setContentSize({
        size.width,
        25.0f,
    });
    m_buttonMenu->setPosition({
        winSize.width / 2.0f,
        (winSize.height / 2.0f) - (size.height / 2.0f) + 25.0f,
    });
    m_mainLayer->addChild(m_buttonMenu, 10);

    // Setup title.
    m_title = CCLabelBMFont::create("", "goldFont.fnt");
    m_title->setPosition({
        winSize.width / 2.0f,
        (winSize.height / 2.0f) + (size.height / 2.0f) - 16.0f,
    });
    m_title->setScale(0.8f);
    m_mainLayer->addChild(m_title);
}

void PrideSelectPopup::setupButtonMenu() {
    const auto size = m_buttonMenu->getContentSize();

    // Setup OK button.
    auto buttonSprite = ButtonSprite::create("OK");
    auto button = CCMenuItemSpriteExtra::create(
        buttonSprite,
        this,
        menu_selector(PrideSelectPopup::onClose)
    );
    button->setPosition(size / 2.0f);
    m_buttonMenu->addChild(button);

    // Setup blur toggle.
    auto toggle = CCMenuItemToggler::createWithStandardSprites(
        this,
        menu_selector(PrideSelectPopup::onBlur),
        0.7f
    );
    toggle->setSizeMult(1.5f);
    toggle->setPosition({
        25.0f,
        size.height / 2.0f
    });
    m_buttonMenu->addChild(toggle);

    // Setup label for blur toggle.
    auto label = CCLabelBMFont::create("Blur", "bigFont.fnt");
    label->setAnchorPoint({ 0.0f, 0.5f });
    label->setScale(0.45f);
    label->setPosition({
        25.0f + 18.0f,
        size.height / 2.0f
    });
    m_buttonMenu->addChild(label);

    // Set toggle state from PrideManager.
    auto PM = PrideManager::sharedManager();
    toggle->toggle(PM->getBlurEnabled());
}

void PrideSelectPopup::setupPage() {
    auto director = CCDirector::sharedDirector();
    auto winSize = director->getWinSize();
    
    const int width = 7;
    const int height = 2;
    const auto size = CCSizeMake(
        (width * 30.0f) + 30.0f,
        (height * 30.0f) + 10.0f
    );

    const auto position = ccp(
        winSize.width / 2.0f,
        (winSize.height / 2.0f) - 40.0f
    );

    // Setup background.
    auto background = CCScale9Sprite::create("square02_001.png");
    background->setContentSize(size);
    background->setPosition(position);
    background->setOpacity(75);
    m_mainLayer->addChild(background, -1);

    // Setup menu.
    m_iconMenu = CCMenu::create();
    m_iconMenu->ignoreAnchorPointForPosition(false);
    m_iconMenu->setContentSize(size);
    m_iconMenu->setPosition(position);
    m_mainLayer->addChild(m_iconMenu, 11);

    // Setup streak icons.
    auto PM = PrideManager::sharedManager();
    int numStreaks = PM->getNumStreaks();

    for (int i = 0; i < PM->getNumStreaks(); i++) {
        const int x = i % width;
        const int y = i / width;

        auto sprite = CCSprite::createWithSpriteFrame(
            PM->getStreakIcon(i)
        );
        sprite->setScale(0.8f);

        auto menuItem = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(PrideSelectPopup::onSelect)
        );
        menuItem->setTag(i);
        menuItem->setPosition({
            30.0f + (x * 30.0f),
            (size.height - 20.0f) - (y * 30.0f),
        });

        m_iconMenu->addChild(menuItem);
    }
    
    // Setup cursor.
    m_cursor = CCSprite::createWithSpriteFrameName("GJ_select_001.png");
    m_cursor->setScale(0.85f);
    m_iconMenu->addChild(m_cursor, 1);

    // This is required for the menu to work properly.
    // Why does this work?
    handleTouchPriority(this);
}

void PrideSelectPopup::setupPreview() {
    auto director = CCDirector::sharedDirector();
    auto winSize = director->getWinSize();

    const CCPoint position = {
        winSize.width / 2.0f,
        (winSize.height / 2.0f) + 50.0f,
    };

    const CCSize size = { 250.0f, 80.0f };

    // Setup stencil.
    auto stencil = CCScale9Sprite::create("square02_001.png");
    stencil->setContentSize(size - 1.0f); // Unfuck edges
    stencil->setPosition(position);
    m_mainLayer->addChild(stencil);

    // Setup preview layer.
    m_preview = PridePreviewLayer::create();
    m_preview->setPosition(position);

    // Setup clipping node.
    auto clippingNode = CCClippingNode::create();
    clippingNode->setStencil(stencil);
    clippingNode->setAlphaThreshold(0.7f);
    clippingNode->addChild(m_preview);
    m_mainLayer->addChild(clippingNode);
    
    // Setup border.
    auto border = CCScale9Sprite::create("commentBorder.png"_spr);
    border->setColor({ 130, 64, 32 }); // Happy textures
    border->setContentSize(size);
    border->setPosition(position);
    border->setZOrder(1);
    m_mainLayer->addChild(border);
}

void PrideSelectPopup::select(int id, bool playEffect) {
    auto PM = PrideManager::sharedManager();
    auto data = PM->getStreakData(id);

    // Update title.
    m_title->setCString(data.name.c_str());

    // Update cursor position.
    auto icon = m_iconMenu->getChildByTag(id);
    m_cursor->setPosition(icon->getPosition());

    // Update player preview.
    m_preview->getPlayer()->setStreak(
        id,
        PM->getBlurEnabled(),
        playEffect
    );
}

void PrideSelectPopup::onClose(CCObject* sender) {
    removeFromParentAndCleanup(true);
}

void PrideSelectPopup::onBlur(CCObject* sender) {
    auto toggle = static_cast<CCMenuItemToggler*>(sender);

    // Why is this inverted?    
    bool enabled = !toggle->isToggled();

    auto PM = PrideManager::sharedManager();
    PM->setBlurEnabled(enabled);

    select(PM->getStreakID(), false);
}

void PrideSelectPopup::onSelect(CCObject* sender) {
    auto icon = static_cast<CCMenuItemSpriteExtra*>(sender);
    int streak = icon->getTag();

    // Update current streak.
    auto PM = PrideManager::sharedManager();
    int lastStreak = PM->getStreakID();
    PM->setStreakID(streak);

    bool playEffect = (streak != lastStreak);

    select(streak, playEffect);
    m_callback(streak);
}

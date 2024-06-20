#include "PridePreviewLayer.hpp"
#include <new>

using namespace geode::prelude;

PridePreviewLayer* PridePreviewLayer::create() {
    auto ret = new (std::nothrow) PridePreviewLayer();

    if (ret && ret->init()) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}

bool PridePreviewLayer::init() {
    if (!CCNode::init()) {
        return false;
    }

    const CCSize contentSize = { 400.0f, 100.0f };
    setContentSize(contentSize);
    ignoreAnchorPointForPosition(false);
    
    auto GM = GameManager::sharedState();

    // Setup background.
    m_background = CCSprite::create(GM->getBGTexture(1));
    m_background->setPosition(contentSize / 2.0f);
    m_background->setScale(0.8f);
    m_background->setColor({ 0x00, 0x66, 0xff });
    m_background->setZOrder(-1);

    ccTexParams texParams = {
        GL_LINEAR,
        GL_LINEAR,
        GL_REPEAT,
        GL_REPEAT,
    };
    m_background->getTexture()->setTexParameters(&texParams);
    addChild(m_background);

    // Setup player.
    m_player = PrideFakePlayer::create();
    m_player->setPosition({
        (contentSize.width / 2.0f) + 45.0f,
        contentSize.height / 2.0f
    });
    addChild(m_player);

    scheduleUpdate();
    return true;
}

void PridePreviewLayer::update(float delta) {
    m_clkTimer += delta;

    auto textureRect = CCRectMake(
        m_clkTimer * 10.0f,
        256.0f,
        400.0f,
        100.0f
    );
    m_background->setTextureRect(textureRect);
}

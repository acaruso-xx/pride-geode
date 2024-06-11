#include "PridePlayerShipSprite.hpp"

#include <new>
#include <fmt/format.h>

using namespace geode::prelude;

PridePlayerShipSprite* PridePlayerShipSprite::create(const CreateArg& args) {
    auto ret = new (std::nothrow) PridePlayerShipSprite();

    if (ret && ret->init(args)) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}

bool PridePlayerShipSprite::init(const CreateArg& args) {
    if (!CCNode::init()) {
        return false;
    }

    setAnchorPoint({ 0.5f, 0.5f });
    ignoreAnchorPointForPosition(false);

    // Request icon.
    auto GM = GameManager::sharedState();
    m_iconRequestID = GM->getIconRequestID();
    GM->loadIcon(args.playerFrame, 0, m_iconRequestID);
    GM->loadIcon(args.playerShip, 1, m_iconRequestID);

    setupPassenger(args.playerFrame);
    setupVehicle(args.playerShip);

    updateColor(
        args.playerColor,
        args.playerColor2,
        args.playerColor3,
        args.playerGlow
    );
    
    return true;
}

CCSprite* PridePlayerShipSprite::addSprite(
    const std::string& format,
    int frame,
    float y,
    float scale,
    int zOrder
) {
    auto frameName = fmt::format(fmt::runtime(format), frame);
    auto sprite = CCSprite::createWithSpriteFrameName(frameName.c_str());

    if (sprite == nullptr) {
        return nullptr;
    }

    sprite->setPositionY(y);
    sprite->setScale(scale);
    sprite->setZOrder(zOrder);
    addChild(sprite);

    return sprite;
}

void PridePlayerShipSprite::setupPassenger(int frame) {
    auto add = [this, frame](const std::string& format, int zOrder) {
        return addSprite(format, frame, 5.0f, 0.55f, zOrder);
    };

    m_passengerSprite      = add("player_{:02}_001.png",       0);
    m_passengerSprite2     = add("player_{:02}_2_001.png",    -1);
    m_passengerSpriteGlow  = add("player_{:02}_glow_001.png", -2);
    m_passengerSpriteExtra = add("player_{:02}_extra_001.png", 1);
}

void PridePlayerShipSprite::setupVehicle(int frame) {
    auto add = [this, frame](const std::string& format, int zOrder) {
        return addSprite(format, frame, -5.0f, 1.0f, zOrder);
    };

    m_vehicleSprite      = add("ship_{:02}_001.png",       3);
    m_vehicleSprite2     = add("ship_{:02}_2_001.png",     2);
    m_vehicleSpriteGlow  = add("ship_{:02}_glow_001.png", -2);
    m_vehicleSpriteExtra = add("ship_{:02}_extra_001.png", 4);
}

void PridePlayerShipSprite::updateColor(
    const cocos2d::ccColor3B& color,
    const cocos2d::ccColor3B& color2,
    const cocos2d::ccColor3B& color3,
    bool glow
) {
    m_passengerSprite->setColor(color);
    m_vehicleSprite->setColor(color);

    m_passengerSprite2->setColor(color2);
    m_vehicleSprite2->setColor(color2);

    if (glow) {
        m_passengerSpriteGlow->setColor(color3);
        m_vehicleSpriteGlow->setColor(color3);
    } else {
        m_passengerSpriteGlow->setVisible(false);
        m_vehicleSpriteGlow->setVisible(false);
    }
}

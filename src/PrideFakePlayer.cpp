#include "PrideFakePlayer.hpp"

#include <cmath>
#include <new>
#include "PrideManager.hpp"

using namespace geode::prelude;

PrideFakePlayer* PrideFakePlayer::create() {
    auto ret = new (std::nothrow) PrideFakePlayer();

    if (ret && ret->init()) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}

bool PrideFakePlayer::init() {
    if (!CCNode::init()) {
        return false;
    }

    setupPlayer();
    setupStreak();

    scheduleUpdate();
    return true;
}

void PrideFakePlayer::setupPlayer() {
    auto GM = GameManager::sharedState();

    m_ship = PridePlayerShipSprite::create({
        GM->getPlayerFrame(),
        GM->getPlayerShip(),
        GM->getPlayerGlow(),
        GM->colorForIdx(GM->getPlayerColor()),
        GM->colorForIdx(GM->getPlayerColor2()),
        GM->colorForIdx(GM->getPlayerGlowColor())
    });

    addChild(m_ship);
};

void PrideFakePlayer::setupStreak() {
    auto PM = PrideManager::sharedManager();

    // Setup normal streak.
    // Parameters are tweaked to look half-decent.
    m_streak = PrideFakeStreak::create(
        0.8f,
        14.0f,
        { 0xf7, 0xf6, 0xb8 },
        PM->getStreakTexture(
            PM->getStreakID(),
            PM->getBlurEnabled()
        ),
        150.0f
    );

    // I don't know where these numbers come from,
    // but they are definitely correct.
    m_streak->setPosition({ -8.0f, -9.0f });
    m_streak->setZOrder(-2);
    addChild(m_streak);
}

void PrideFakePlayer::update(float delta) {
    m_clkTimer += delta;

    const float wavelength = -2.0f;
    const float amplitude = 8.0f;

    float y = std::sin(m_clkTimer * wavelength) * amplitude;
    float theta = std::cos(m_clkTimer * wavelength) * amplitude;

    m_ship->setPositionY(y);
    m_ship->setRotation(theta);

    // This... works?
    auto transform = m_ship->nodeToParentTransform();
    auto streakPos = CCPointApplyAffineTransform(
        { -8.0f, -9.0f },
        transform
    );
    m_streak->setPosition(streakPos);
}

void PrideFakePlayer::setStreak(int id, bool blur, bool playEffect) {
    auto PM = PrideManager::sharedManager();
    auto texture = PM->getStreakTexture(id, blur);

    m_streak->setTexture(texture);

    if (playEffect) {
        playRainbowEffect(
            PM->getStreakData(id).colors
        );
    }
}

void PrideFakePlayer::playRainbowEffect(
    const std::array<ccColor3B, 3>& colors
) {
    auto first = CCCircleWave::create(4.0f, 62.0f * 0.75f, 0.5f, false);
    first->m_color = colors[0];
    first->m_blendAdditive = true;
    first->m_opacityMod = 0.8f;
    first->m_lineWidth = 4;
    first->m_circleMode = CircleMode::Outline;
    m_ship->addChild(first, -10);

    auto second = CCCircleWave::create(1.0f, 60.0f * 0.75f, 0.5f, false);
    second->m_color = colors[1];
    second->m_blendAdditive = true;
    second->m_opacityMod = 0.8f;
    second->m_lineWidth = 4;
    second->m_circleMode = CircleMode::Outline;
    m_ship->addChild(second, -10);

    auto third = CCCircleWave::create(20.0f, 60.0f * 0.75f, 0.5f, false);
    third->m_color = colors[2];
    third->m_blendAdditive = true;
    third->m_opacityMod = 1.0f;
    m_ship->addChild(third, -10);
}

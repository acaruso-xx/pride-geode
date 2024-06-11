#pragma once

#include <Geode/Geode.hpp>

#include <array>
#include "PrideFakeStreak.hpp"
#include "PridePlayerShipSprite.hpp"

/// @brief Non-functional player that moves in a sine-wave.
class PrideFakePlayer final : public cocos2d::CCNode {
public:
    /// @brief Create fake player.
    /// @return Fake player.
    static PrideFakePlayer* create();

    /// @brief Initialize fake player.
    /// @return Whether the initialization was successful.
    bool init() override;

    /// @brief Update sine motion.
    /// @param delta Delta time.
    void update(float delta) override;

    /// @brief Set streak texture.
    /// @param id Streak ID.
    /// @param blur Whether blur is enabled.
    /// @param playEffect Whether to play rainbow effect.
    void setStreak(int id, bool blur, bool playEffect);

private:
    /// @brief Setup player sprite.
    void setupPlayer();

    /// @brief Setup streak and ship fire.
    void setupStreak();

    /// @brief Play rainbow effect.
    /// @param colors Colors for effect.
    void playRainbowEffect(const std::array<cocos2d::ccColor3B, 3>& colors);

    float m_clkTimer;

    PridePlayerShipSprite* m_ship;
    PrideFakeStreak* m_streak;
    PrideFakeStreak* m_shipStreak;
};

#pragma once

#include <Geode/Geode.hpp>
#include "PrideFakePlayer.hpp"

/// @brief Streak preview layer.
class PridePreviewLayer final : public cocos2d::CCLayer {
public:
    /// @brief Create preview layer.
    /// @return Preview layer.
    static PridePreviewLayer* create();

    /// @brief Initialize preview layer.
    /// @return Whether the initialization was successful.
    bool init() override;

    /// @brief Update scrolling background.
    /// @param delta Delta time.
    void update(float delta) override;

    /// @brief Get player.
    /// @return Player.
    PrideFakePlayer* getPlayer() {
        return m_player;
    }

private:
    float m_clkTimer;

    cocos2d::CCSprite* m_background;
    PrideFakePlayer* m_player;
};
#pragma once

#include <Geode/Geode.hpp>

/// @brief Motion streak with simulated X velocity.
class PrideFakeStreak final : public cocos2d::CCMotionStreak {
public:
    /// @brief Create fake streak.
    /// @param fade Fade in seconds.
    /// @param stroke Stroke width.
    /// @param color Stroke color.
    /// @param texture Stroke texture.
    /// @param speed Simulated X velocity.
    /// @return Fake streak.
    static PrideFakeStreak* create(
        float fade,
        float stroke,
        const cocos2d::ccColor3B& color,
        cocos2d::CCTexture2D* texture,
        float speed
    );

    /// @brief Initialize fake streak.
    /// @param fade Fade in seconds.
    /// @param stroke Stroke width.
    /// @param color Stroke color.
    /// @param texture Stroke texture.
    /// @param speed Simulated X velocity.
    /// @return Whether the initialization was successful.
    bool init(
        float fade,
        float stroke,
        const cocos2d::ccColor3B& color,
        cocos2d::CCTexture2D* texture,
        float speed
    );

    /// @brief Update fake motion.
    /// @param delta Delta time.
    void update(float delta) override;

private:
    float m_speed;
};

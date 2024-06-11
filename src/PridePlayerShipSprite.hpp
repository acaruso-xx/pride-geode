#pragma once

#include <Geode/Geode.hpp>

/// @brief Player ship sprite preview.
class PridePlayerShipSprite final : public cocos2d::CCNode {
public:
    /// @brief Arguments passed to create method.
    struct CreateArg {
        int playerFrame;
        int playerShip;
        bool playerGlow;
        cocos2d::ccColor3B playerColor;
        cocos2d::ccColor3B playerColor2;
        cocos2d::ccColor3B playerColor3;
    };

    /// @brief Create player ship sprite.
    /// @param args Arguments.
    /// @return Player ship sprite.
    static PridePlayerShipSprite* create(const CreateArg& args);

    /// @brief Initialize player ship sprite.
    /// @param arg Arguments.
    /// @return Whether the initialization was successful.
    bool init(const CreateArg& args);

private:
    /// @brief Setup "passenger" sprite.
    /// @param frame Player frame.
    /// @param glow Glow enabled.
    void setupPassenger(int frame);
    
    /// @brief Setup vehicle sprite.
    /// @param frame Player ship frame.
    /// @param glow Glow enabled.
    void setupVehicle(int frame);

    /// @brief Update sprite colors.
    /// @param color Main color.
    /// @param color2 Secondary color.
    /// @param color3 Glow color.
    /// @param glow Glow enabled.
    void updateColor(
        const cocos2d::ccColor3B& color,
        const cocos2d::ccColor3B& color2,
        const cocos2d::ccColor3B& color3,
        bool glow
    );

    /// @brief Sprite creation helper.
    /// @param format Format string.
    /// @param frame Icon frame.
    /// @param y Sprite Y position.
    /// @param scale Sprite scale.
    /// @param zOrder Sprite Z order.
    /// @return Created sprite or nullptr.
    cocos2d::CCSprite* addSprite(
        const std::string& format,
        int frame,
        float y,
        float scale,
        int zOrder
    );

    int m_iconRequestID;

    cocos2d::CCSprite* m_passengerSprite;
    cocos2d::CCSprite* m_passengerSprite2;
    cocos2d::CCSprite* m_passengerSpriteGlow;
    cocos2d::CCSprite* m_passengerSpriteExtra;

    cocos2d::CCSprite* m_vehicleSprite;
    cocos2d::CCSprite* m_vehicleSprite2;
    cocos2d::CCSprite* m_vehicleSpriteGlow;
    cocos2d::CCSprite* m_vehicleSpriteExtra;
};

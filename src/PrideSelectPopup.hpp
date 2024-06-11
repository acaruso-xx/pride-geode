#pragma once

#include <Geode/Geode.hpp>
#include <functional>

#include "PridePreviewLayer.hpp"

/// @brief Streak select popup.
class PrideSelectPopup final : public FLAlertLayer {
public:
    /// @brief Streak update callback type.
    using Callback = std::function<void(int id)>;

    /// @brief Create streak select popup.
    /// @param callback Streak update callback.
    /// @return Streak select popup.
    static PrideSelectPopup* create(const Callback& callback);

    /// @brief Initialize streak select popup.
    /// @param callback Streak update callback.
    /// @return Whether the initialization was successful.
    bool init(const Callback& callback);

    /// @brief Key back clicked callback.
    void keyBackClicked() override;

private:
    /// @brief Setup popup base.
    void setupBase();

    /// @brief Setup OK button and blur button.
    void setupButtonMenu();

    /// @brief Setup streak icons.
    void setupPage();

    /// @brief Setup streak preview.
    void setupPreview();

    /// @brief Update title and cursor position based on selection.
    /// @param id Selected streak ID.
    /// @param effect Whether to play rainbow effect.
    void select(int id, bool playEffect);

    /// @brief Popup closed callback.
    /// @param sender Sender.
    void onClose(cocos2d::CCObject* sender);

    /// @brief On blur toggle clicked callback.
    /// @param sender Sender.
    void onBlur(cocos2d::CCObject* sender);

    /// @brief On streak selected callback.
    /// @param sender Sender.
    void onSelect(cocos2d::CCObject* sender);

    Callback m_callback;
    cocos2d::extension::CCScale9Sprite* m_background;
    cocos2d::CCLabelBMFont* m_title;
    cocos2d::CCMenu* m_iconMenu;
    cocos2d::CCSprite* m_cursor;
    PridePreviewLayer* m_preview;
};

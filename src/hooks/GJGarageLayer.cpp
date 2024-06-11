#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/Geode.hpp>

#include "../PrideManager.hpp"
#include "../PrideSelectPopup.hpp"

using namespace geode::prelude;

class $modify(GJGarageLayer) {
    struct Fields {
        CCSprite* streakIcon;
    };

    void playRainbowEffect() {
        auto PM = PrideManager::sharedManager();
        auto data = PM->getStreakData(PM->getStreakID());
        auto colors = data.colors;

        auto first = CCCircleWave::create(4.0f, 62.0f, 0.5f, false);
        first->m_color = colors[0];
        first->m_blendAdditive = true;
        first->m_opacityMod = 0.8f;
        first->m_lineWidth = 4;
        first->m_circleMode = CircleMode::Outline;
        m_playerObject->addChild(first, -10);

        auto second = CCCircleWave::create(1.0f, 60.0f, 0.5f, false);
        second->m_color = colors[1];
        second->m_blendAdditive = true;
        second->m_opacityMod = 0.8f;
        second->m_lineWidth = 4;
        second->m_circleMode = CircleMode::Outline;
        m_playerObject->addChild(second, -10);

        auto third = CCCircleWave::create(20.0f, 60.0f, 0.5f, false);
        third->m_color = colors[2];
        third->m_blendAdditive = true;
        third->m_opacityMod = 1.0f;
        m_playerObject->addChild(third, -10);
    }

    void showUnlockPopup(int icon, UnlockType unlockType) {
        // Replace unlock popup with streak select UI.
        if (icon == 2 && unlockType == UnlockType::Streak) {
            PrideSelectPopup::create(
                [this](int id){ setStreakIcon(id); }
            )->show();
            return;
        }

        GJGarageLayer::showUnlockPopup(icon, unlockType);
    }

    void setupSpecialPage() {
        GJGarageLayer::setupSpecialPage();

        // Find rainbow streak icon and save it for later.
        // This is kind of disgusting! I wish there was a better way to do it.
        m_fields->streakIcon = findFirstChildRecursive<CCSprite>(
            m_iconSelection,
            [](auto sprite) {
                return isSpriteFrameName(sprite, "player_special_02_001.png");
            }
        );

        // Update streak icon to current streak.
        auto PM = PrideManager::sharedManager();
        setStreakIcon(PM->getStreakID());
    }

    /// @brief Set rainbow streak icon for streak ID.
    /// @param id Streak ID.
    void setStreakIcon(int id) {
        auto PM = PrideManager::sharedManager();

        auto frame = PM->getStreakIcon(id);
        m_fields->streakIcon->setDisplayFrame(frame);
    }
};

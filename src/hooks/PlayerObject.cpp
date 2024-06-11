#include <Geode/modify/PlayerObject.hpp>
#include <Geode/Geode.hpp>

#include "../PrideManager.hpp"

using namespace geode::prelude;

class $modify(PlayerObject) {
    void setupStreak() {
        PlayerObject::setupStreak();

        // Ignore if we aren't using rainbow streak.
        if (m_playerStreak != 2) {
            return;
        }

        // Replace streak texture.
        auto PM = PrideManager::sharedManager();
        auto texture = PM->getStreakTexture(
            PM->getStreakID(),
            PM->getBlurEnabled()
        );

        m_regularTrail->setTexture(texture);
    }
};

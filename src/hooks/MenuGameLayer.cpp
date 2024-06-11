#include <Geode/modify/MenuGameLayer.hpp>
#include <Geode/Geode.hpp>

#include <cstdlib>
#include "../PrideManager.hpp"

using namespace geode::prelude;

class $modify(MenuGameLayer) {
    void resetPlayer() {
        MenuGameLayer::resetPlayer();

        // Get random streak texture.
        auto PM = PrideManager::sharedManager(); 
        auto texture = PM->getStreakTexture(
            std::rand() % PM->getNumStreaks(),
            PM->getBlurEnabled()
        );

        // Set motion streak parameters.
        auto streak = m_playerObject->m_regularTrail;
        streak->initWithFade(
            0.3f,
            5.0f,
            14.0f,
            { 0xF7, 0xF6, 0xB8 },
            texture
        );

        // Set additive blending.
        streak->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
    }
};

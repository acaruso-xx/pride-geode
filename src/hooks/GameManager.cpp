#include <Geode/modify/GameManager.hpp>
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class $modify(GameManager) {
    bool isIconUnlocked(int icon, IconType iconType) {
        // Force-unlock rainbow streak.
        if (icon == 2 & iconType == IconType::Special) {
            return true;
        }

        return GameManager::isIconUnlocked(icon, iconType);
    }
};

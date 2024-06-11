#include "PrideManager.hpp"

#include <new>
#include <string>

using namespace geode::prelude;

PrideManager* PrideManager::s_sharedManager = nullptr;

PrideManager* PrideManager::sharedManager() {
    if (s_sharedManager == nullptr) {
        s_sharedManager = new (std::nothrow) PrideManager();
        s_sharedManager->init();
    }

    return s_sharedManager;
}

bool PrideManager::init() {
    // Load streak data.
    auto fileUtils = CCFileUtils::sharedFileUtils();
    auto path = fileUtils->fullPathForFilename("streaks.json"_spr, false);
    auto json = file::readJson(path).unwrap();

    // Read streak data.
    for (auto streak : json["streaks"].as_array()) {
        m_streakData.push_back(
            streak.as<PrideStreakData>()
        );
    }

    return true;
}

int PrideManager::getNumStreaks() const {
    return m_streakData.size();
}

const PrideStreakData& PrideManager::getStreakData(int id) const {
    return m_streakData[id];
}

CCSpriteFrame* PrideManager::getStreakIcon(int id) const {
    // fmt::runtime is required because of _spr
    std::string frameName = fmt::format(
        fmt::runtime("streak_{:02}_icon_001.png"_spr),
        id
    );

    auto spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    return spriteFrameCache->spriteFrameByName(frameName.c_str());
}

CCTexture2D* PrideManager::getStreakTexture(int id, bool blur) const {
    // fmt::runtime is required because of _spr
    std::string path = blur
        ? fmt::format(fmt::runtime("streak_{:02}_blur_001.png"_spr), id)
        : fmt::format(fmt::runtime("streak_{:02}_001.png"_spr), id);

    auto textureCache = CCTextureCache::sharedTextureCache();
    return textureCache->addImage(path.c_str(), false);
}

int PrideManager::getStreakID() const {
    return getMod()->getSavedValue<int>("streak-id");
}

void PrideManager::setStreakID(int id) {
    getMod()->setSavedValue<int>("streak-id", id);
}

bool PrideManager::getBlurEnabled() const {
    return getMod()->getSavedValue<bool>("blur-enabled");
}

void PrideManager::setBlurEnabled(bool blur) {
    getMod()->setSavedValue<bool>("blur-enabled", blur);
}

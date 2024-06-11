#pragma once

#include <Geode/Geode.hpp>
#include <vector>

#include "PrideStreakData.hpp"

/// @brief Manager singleton.
class PrideManager final {
public:
    /// @brief Get manager singleton.
    /// @return Manager singleton.
    static PrideManager* sharedManager();

    /// @brief Initialize pride manager.
    /// @return Whether the initialization was successful.
    bool init();

    /// @brief Get number of streaks.
    /// @return Number of streaks.
    int getNumStreaks() const;

    /// @brief Get streak data for streak ID.
    /// @param id Streak ID.
    /// @return Streak data.
    const PrideStreakData& getStreakData(int id) const;

    /// @brief Get streak icon sprite frame for streak ID.
    /// @param id Streak ID.
    /// @return Streak icon texture.
    cocos2d::CCSpriteFrame* getStreakIcon(int id) const;

    /// @brief Get streak texture for streak ID.
    /// @param id Streak ID.
    /// @param blur Whether blur is enabled.
    /// @return Streak texture.
    cocos2d::CCTexture2D* getStreakTexture(int id, bool blur) const;

    /// @brief Get current streak ID.
    /// @return Current streak ID.
    int getStreakID() const;

    /// @brief Set current streak ID.
    /// @param id Current streak ID.
    void setStreakID(int id);

    /// @brief Get whether blur is enabled.
    /// @return Whether blur is enabled.
    bool getBlurEnabled() const;

    /// @brief Set whether blur is enabled.
    /// @param blur Whether blur is enabled.
    void setBlurEnabled(bool blur);

private:
    static PrideManager* s_sharedManager;

    std::vector<PrideStreakData> m_streakData;
};

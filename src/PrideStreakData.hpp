#pragma once

#include <Geode/Geode.hpp>
#include <array>
#include <string>

/// @brief Streak data.
struct PrideStreakData final {
    std::string name;
    std::array<cocos2d::ccColor3B, 3> colors; ///< For rainbow effect.
};

template<>
struct matjson::Serialize<PrideStreakData> {
    static PrideStreakData from_json(const matjson::Value& json) {
        return PrideStreakData {
            .name = json["name"].as_string(),
            .colors = {{
                json["colors"][0].as<cocos2d::ccColor3B>(),
                json["colors"][1].as<cocos2d::ccColor3B>(),
                json["colors"][2].as<cocos2d::ccColor3B>(),
            }}
        };
    }
    
    static bool is_json(const matjson::Value& json) {
        return true;
    }
};

#include "PrideFakeStreak.hpp"
#include <new>

using namespace geode::prelude;

PrideFakeStreak* PrideFakeStreak::create(
    float fade,
    float stroke,
    const ccColor3B& color,
    CCTexture2D* texture,
    float speed
) {
    auto ret = new (std::nothrow) PrideFakeStreak();

    if (ret && ret->init(fade, stroke, color, texture, speed)) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}

bool PrideFakeStreak::init(
    float fade,
    float stroke,
    const ccColor3B& color,
    CCTexture2D* texture,
    float speed
) {
    // Setting minSeg to 5.0f fixes all of the problems I've been having.
    // I don't know why.
    if (!initWithFade(fade, 5.0f, stroke, color, texture)) {
        return false;
    }

    m_speed = speed;

    // When I was testing this, the streak wouldn't work properly unless
    // this was unset. Now it works fine?
    setFastMode(false);

    // Additive blending.
    setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
    
    return true;
}

void PrideFakeStreak::update(float delta) {
    CCMotionStreak::update(delta);

    // Move all points to simulate motion.
    for (unsigned int i = 0; i < m_uNuPoints; i++) {
        m_pPointVertexes[i].x -= (m_speed * delta);
    }
}

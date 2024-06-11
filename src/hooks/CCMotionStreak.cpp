#include <Geode/modify/CCMotionStreak.hpp>
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class $modify(CCMotionStreak) {
    struct Fields {
        bool isChecked;
        bool isFlipped;
    };

    bool initWithFade(
        float fade,
        float minSeg,
        float stroke,
        const ccColor3B& color,
        CCTexture2D* texture
    ) {
        if (!CCMotionStreak::initWithFade(
            fade,
            minSeg,
            stroke,
            color,
            texture
        )) {
            return false;
        }

        m_fields->isChecked = false;
        m_fields->isFlipped = false;
        return true;
    }

    void resumeStroke() {
        CCMotionStreak::resumeStroke();

        m_fields->isChecked = false;
        m_fields->isFlipped = false;
    }

    void reset() {
        CCMotionStreak::reset();

        m_fields->isChecked = false;
        m_fields->isFlipped = false;
    }

    void update(float delta) {
        CCMotionStreak::update(delta);

        // This method has been amended to check if the streak is generating
        // upside-down, and correct the texture coordinates if so.
        
        // It doesn't work 100% reliably, but it works well enough to fix the
        // preview UI. I don't care!

        if (!m_bStartingPositionInitialized) {
            return;
        }

        // We can't check anything if there's only one point!
        if (m_uNuPoints < 2) {
            return;
        }

        // Check if motion streak is generating upside down, if it hasn't been
        // checked already.
        if (!m_fields->isChecked) {
            m_fields->isChecked = true;

            const auto p1 = m_pVertices[0];
            const auto p2 = m_pVertices[1];

            if (p1.y < p2.y) {
                // Streak is generating upside-down.
                // Set flipped flag.

                m_fields->isFlipped = true;
            }
        }

        // Regenerate flip texture coordinates if flipped flag is set.
        if (m_fields->isFlipped) {
            const float texDelta = 1.0f / m_uNuPoints;
            for (unsigned int i = 0; i < m_uNuPoints; i++) {
                m_pTexCoords[i * 2] = tex2(1.0f, texDelta);
                m_pTexCoords[i * 2 + 1] = tex2(0.0f, texDelta);
            }
        }
    }
};

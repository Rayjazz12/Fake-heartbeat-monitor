// Heart Rate Monitor — fake heartbeat model + config
// Believable readings: steps in 2–3 bpm (never ±1), holds a value most
// of the time, and after you die the reading holds at a high BPM a bit
// before relaxing to a resting value instead of snapping down immediately.

#pragma once

#include <cstdint>
#include <algorithm>
#include <random>

namespace HeartRate {

struct Config {
    int restingBpm = 82;
    int peakBpm = 137;
    int step = 3;
    float readSpeed = 1.0f;
    bool keepsRateOnDeath = true;
    float deathHoldSec = 2.2f;
    float decayTimeSec = 95.0f;

    Config() = default;
    void setDefaults() {
        restingBpm = 82; peakBpm = 137;
        step = 3; readSpeed = 1.0f;
        keepsRateOnDeath = true;
        deathHoldSec = 2.2f; decayTimeSec = 95.0f;
    }
};

class Model {
public:
    explicit Model(Config cfg) : m_cfg(cfg), m_rng(std::random_device{}()) {
        reset();
    }

    void setConfig(Config cfg) {
        m_cfg = cfg;
        m_cfg.setDefaults();
        reset();
    }

    void reset() {
        m_current = (float)m_cfg.restingBpm;
        m_peak = (float)m_cfg.peakBpm;
        m_deathMode = false;
        m_holdRemaining = 0.0f;
        m_rng.seed(std::random_device()());
    }

    int step() {
        if (m_deathMode) {
            if (m_holdRemaining > 0.0f) {
                m_holdRemaining -= m_dt;
                if (m_holdRemaining <= 0.0f) {
                    m_deathMode = false;
                    m_holdRemaining = 0.0f;
                }
            }
            return (int)std::round(m_current);
        }

        float pulse = (float)m_rng / (float)RAND_MAX;
        if (pulse < 0.32f) {
            return (int)std::round(m_current);
        }

        int s = (m_rng() % 2) == 0 ? 2 : 3;
        float dir = (m_current < m_peak) ? 1.0f : ((m_current > m_peak) ? -1.0f : 0.0f);
        if (dir == 0.0f) dir = 1.0f;

        int nxt = (int)(m_current + dir * s);
        if (nxt >= m_peak) nxt = m_peak;
        if (nxt <= 40) nxt = 40;
        m_current = (float)nxt;

        m_current = m_current * 0.75f + (float)nxt * 0.25f;
        return (int)std::round(m_current);
    }

    void onDeath() {
        if (!m_deathMode) {
            m_deathMode = true;
            m_holdRemaining = m_cfg.deathHoldSec;
        }
    }

    void update(float dt) {
        m_dt = dt;
        if (m_deathMode && m_holdRemaining > 0.0f) {
            m_holdRemaining -= dt;
            if (m_holdRemaining <= 0.0f) {
                m_deathMode = false;
                m_holdRemaining = 0.0f;
            }
            return;
        }

        if (m_deathMode) {
            float target = (float)m_cfg.restingBpm;
            float frac = 1.0f - std::exp(-dt / m_cfg.decayTimeSec);
            m_current = m_current + (target - m_current) * frac;
            return;
        }

        if (m_current < m_peak) {
            float pulse = (float)m_rng / (float)RAND_MAX;
            if (pulse < 0.32f) return;
            int s = (m_rng() % 2) == 0 ? 2 : 3;
            int nxt = (int)(m_current + (float)s);
            if (nxt >= m_peak) nxt = m_peak;
            m_current = (float)nxt;
        } else {
            float p = (float)m_rng / (float)RAND_MAX;
            if (p > 0.32f) {
                int nxt = (int)(m_current - 3.0f);
                if (nxt < 40) nxt = 40;
                m_current = (float)nxt;
            }
        }
    }

    int getDisplay() const { return (int)std::round(m_current); }
    bool isDeathMode() const { return m_deathMode; }

private:
    Config m_cfg;
    float m_current;
    float m_peak;
    bool m_deathMode;
    float m_holdRemaining;
    float m_dt;
    std::mt19937 m_rng;
};

} // namespace HeartRate

// Settings.hpp — simplified settings for the standalone in-level heart monitor.
// 12 settings: styling + rate model + death behaviour.

#pragma once

#include <Geode/Geode.hpp>
#include <string>

namespace HeartRate {

struct Settings {
    // Styling
    int corner = 1;
    int margin = 10;
    float scale = 1.0f;
    int opacity = 82;
    std::string colour = "#a6de00";

    // Rate model
    std::string rateTitle = "RATE";
    int restingBpm = 82;
    int peakBpm = 137;
    int bpmStep = 3;
    float readSpeed = 1.0f;

    // Death
    bool keepsRateOnDeath = true;
    float deathHold = 2.2f;
    float deathRecovery = 95.0f;

    void setDefaults() {
        corner = 1; margin = 10; scale = 1.0f; opacity = 82;
        colour = "#a6de00";
        rateTitle = "RATE";
        restingBpm = 82; peakBpm = 137;
        bpmStep = 3; readSpeed = 1.0f;
        keepsRateOnDeath = true;
        deathHold = 2.2f; deathRecovery = 95.0f;
    }
};

} // namespace HeartRate

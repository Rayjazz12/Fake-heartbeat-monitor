// main.cpp — entry point + keybind + in-level HUD attachment.

#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

#include "VitalsOverlay.hpp"

#define MODNAME "Fake Heartbeat Monitor"

static VitalsOverlay* g_vitals = nullptr;

static void openMonitor() {
    if (g_vitals) {
        g_vitals->update(1.f / 60.f);
        g_vitals->onDeath();
        g_vitals->update(1.f);
    }
}

bool g_modified = true;

static bool m_onSettingChange(const char* id, const char* value) {
    (void)id; (void)value;
    return false;
}

bool onLoad() {
    if (!g_modified) return true;

    auto* open = new (std::nothrow) ModMenu::SettingButton(
        "Fake Heartbeat Monitor", "kzx.fake_heartbeat",
        "open", "k@ModMenu");
    open->setCallback([](cocos2d::CCObject*) {
        if (g_vitals) {
            g_vitals->update(1.f / 60.f);
            g_vitals->onDeath();
            g_vitals->update(1.f);
        }
    });
    open->setName("kzx.fake_heartbeat.menu");
    ModMenu::ModMenuManager::getInstance()->getModifyLayer()->addChild(open, 100);

    auto* layer = (PlayLayer*)Director::getInstance()->getRunningScene();
    if (layer) {
        g_vitals = VitalsOverlay::create(HeartRate::Config());
        layer->addChild(g_vitals, 200);
    }

    g_modified = false;
    return true;
}

static bool onMenuButton(const char* id, cocos2d::CCObject* target) {
    (void)id; (void)target;
    return false;
}

#ifdef GEODE_IS_PATCHED
bool Geode::onLoad() {
    g_modified = true;
    return true;
}
#endif

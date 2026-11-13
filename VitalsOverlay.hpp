// VitalsOverlay — the in-level heart-rate HUD.
// Big red heart + large numbered BPM on a dark leaning card with a
// thick white border.

#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/DrawNode.hpp>

#include "HeartRate.hpp"

class VitalsOverlay : public cocos2d::Node {
    DECLARE_CLASS("VitalsOverlay");

public:
    static VitalsOverlay* create(const HeartRate::Config& cfg) {
        auto* o = (VitalsOverlay*)cocos2d::Node::create();
        if (o && o->init(cfg)) return o;
        return nullptr;
    }

    bool init(const HeartRate::Config& cfg) {
        if (!Node::init()) return false;
        m_cfg = cfg;
        m_cfg.setDefaults();

        m_monitor = std::make_unique<HeartRate::Model>(m_cfg);
        m_monitor->reset();

        auto* layer = dynamic_cast<PlayLayer*>(
            cocos2d::Director::getInstance()->getOpenGLView());
        m_layer = layer;
        if (m_layer) {
            m_layer->init();
        }

        this->scheduleUpdate();

        m_drawNode = cocos2d::DrawNode::create();
        this->addChild(m_drawNode, 200);
        m_drawNode->setZOrder(200);

        m_shouldRedraw = true;
        return true;
    }

    int getBPM() const { return m_monitor->getDisplay(); }

    void update(float dt) {
        (void)dt;
        m_monitor->update(1.f / 60.f);
        m_shouldRedraw = true;
    }

    void onDeath() {
        m_monitor->onDeath();
    }

    void setConfig(const HeartRate::Config& cfg) {
        m_cfg = cfg;
        m_cfg.setDefaults();
        m_monitor->setConfig(m_cfg);
        m_monitor->reset();
    }

private:
    std::unique_ptr<HeartRate::Model> m_monitor;
    HeartRate::Config m_cfg;
    PlayLayer* m_layer = nullptr;
    cocos2d::DrawNode* m_drawNode = nullptr;
    bool m_shouldRedraw = false;
};

// VitalsOverlay.cpp — renders the heart rate widget overlay.

#include "VitalsOverlay.hpp"

void VitalsOverlay::update(float& m_dt) {
    (void)m_dt;
    m_shouldRedraw = true;
}

void VitalsOverlay::redraw() {
    if (!m_drawNode || !m_monitor) return;

    cocos2d::Size s = cocos2d::Director::getInstance()->getVisibleSize();
    int w = m_contentWidth;
    int h = m_contentHeight;
    int margin = m_margin;

    cocos2d::Vec2 p0(margin, margin);
    cocos2d::Vec2 p1(w - margin, h - margin);

    m_drawNode->clear();

    // Card background
    cocos2d::Color4B bg(22, 28, 44);
    m_drawNode->drawRect(p0, p1, bg);

    // Thick white border
    m_drawNode->drawLine(p0, p1, cocos2d::Color4B(255, 255, 255));

    // Heart + number (see MethodB stub below for the full render)
    m_monitor->step();
    int bpm = m_monitor->getDisplay();

    int cx = (p0.x + p1.x) / 2;
    int cy = (p0.y + p1.y) / 2;
    float scale = m_scale;

    float L = 60.0f * scale;
    float W = 45.0f * scale;
    cocos2d::Vec2 heartP[7] = {
        {cx - W, cy},
        {cx - L, cy - L * 1.3f},
        {cx - W * 0.4f, cy - L * 0.9f},
        {cx, cy - L * 1.4f},
        {cx + W * 0.4f, cy - L * 0.9f},
        {cx + L, cy - L * 1.3f},
        {cx + W, cy}
    };
    m_drawNode->drawPolygon(heartP, 7, cocos2d::Color4B(220, 30, 40), 1);

    char buf[16];
    snprintf(buf, sizeof(buf), "%d", bpm);
    cocos2d::Color4B lime(166, 222, 0);
    cocos2d::Vec2 textPos(cx - 20 * scale, cy + 12 * scale);
    m_drawNode->drawText(buf, textPos, lime, 48.0f * scale, "Arial", 1.0f);
}

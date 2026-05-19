#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    // On crée une variable pour garder une trace de notre calque noir
    CCLayerColor* m_brightnessOverlay = nullptr;

    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        // 1. On récupère la valeur actuelle de la barre
        double darknessValue = Mod::get()->getSettingValue<double>("screen-darkness");
        GLubyte opacity = static_cast<GLubyte>(darknessValue * 255.0);

        // 2. On crée le calque et on le stocke dans notre variable m_fields
        m_fields->m_brightnessOverlay = CCLayerColor::create(ccc4(0, 0, 0, opacity));
        m_fields->m_brightnessOverlay->setZOrder(-1);
        this->addChild(m_fields->m_brightnessOverlay);

        // 3. LA MAGIE : On écoute les changements de la barre en direct !
        this->listenForSettingChanges("screen-darkness", [this](double newValue) {
            if (m_fields->m_brightnessOverlay) {
                // Dès que la barre bouge, on recalcule et on applique l'opacité direct !
                GLubyte newOpacity = static_cast<GLubyte>(newValue * 255.0);
                m_fields->m_brightnessOverlay->setOpacity(newOpacity);
            }
        });

        return true;
    }
};

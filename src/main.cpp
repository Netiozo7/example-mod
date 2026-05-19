#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    // On déclare la structure Fields pour que Geode puisse y lier notre calque
    struct Fields {
        CCLayerColor* m_brightnessOverlay = nullptr;
    };

    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        // 1. On récupère la valeur actuelle de la barre
        double darknessValue = Mod::get()->getSettingValue<double>("screen-darkness");
        GLubyte opacity = static_cast<GLubyte>(darknessValue * 255.0);

        // 2. On crée le calque et on l'enregistre proprement dans m_fields
        m_fields->m_brightnessOverlay = CCLayerColor::create(ccc4(0, 0, 0, opacity));
        m_fields->m_brightnessOverlay->setZOrder(-1);
        this->addChild(m_fields->m_brightnessOverlay);

        // 3. On écoute les changements en direct
        this->listenForSettingChanges("screen-darkness", [this](double newValue) {
            if (m_fields->m_brightnessOverlay) {
                GLubyte newOpacity = static_cast<GLubyte>(newValue * 255.0);
                m_fields->m_brightnessOverlay->setOpacity(newOpacity);
            }
        });

        return true;
    }
};

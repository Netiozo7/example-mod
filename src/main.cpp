#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        // 1. On récupère la valeur de ta barre (par défaut 0.5)
        double darknessValue = Mod::get()->getSettingValue<double>("screen-darkness");

        // 2. On convertit en opacité (0 à 255)
        GLubyte opacity = static_cast<GLubyte>(darknessValue * 255.0);

        // 3. On crée le calque noir géant
        auto brightnessOverlay = CCLayerColor::create(ccc4(0, 0, 0, opacity));
        
        // 4. ON LE MET TOUT DEVANT (ZOrder très haut)
        brightnessOverlay->setZOrder(100);
        
        // 5. On désactive les clics dessus pour pouvoir cliquer à travers sur les boutons du menu
        brightnessOverlay->setTouchEnabled(false);
        
        // 6. On l'ajoute au menu
        this->addChild(brightnessOverlay);

        return true;
    }
};

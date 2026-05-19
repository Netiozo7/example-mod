#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        // 1. On récupère la valeur de la barre (entre 0.0 et 1.0, défaut 0.5)
        double darknessValue = Mod::get()->getSettingValue<double>("screen-darkness");

        // 2. On convertit ça en opacité pour Cocos2d (entre 0 et 255)
        GLubyte opacity = static_cast<GLubyte>(darknessValue * 255.0);

        // 3. On crée le calque avec l'opacité choisie
        auto brightnessOverlay = CCLayerColor::create(ccc4(0, 0, 0, opacity));
        
        // 4. On le place sous les boutons pour ne pas bloquer les clics
        brightnessOverlay->setZOrder(-1);
        
        // 5. On l'ajoute à l'écran
        this->addChild(brightnessOverlay);

        return true;
    }
};

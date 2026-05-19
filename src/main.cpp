#include <Geode/Geode.hpp>
#include <Geode/modify/CCScene.hpp>

using namespace geode::prelude;

// On intercepte la classe de base de toutes les scènes du jeu
class $modify(MyCCScene, CCScene) {
    bool init() {
        if (!CCScene::init()) {
            return false;
        }

        // 1. On récupère la configuration de ta barre
        double darknessValue = Mod::get()->getSettingValue<double>("screen-darkness");
        GLubyte opacity = static_cast<GLubyte>(darknessValue * 255.0);

        // 2. On crée le calque noir géant
        auto brightnessOverlay = CCLayerColor::create(ccc4(0, 0, 0, opacity));
        
        // 3. On le met tout devant (ZOrder immense)
        brightnessOverlay->setZOrder(99999);
        
        // 4. On désactive les clics pour pouvoir jouer normalement à travers
        brightnessOverlay->setTouchEnabled(false);
        
        // 5. On l'ajoute directement à la scène globale
        this->addChild(brightnessOverlay);

        return true;
    }
};

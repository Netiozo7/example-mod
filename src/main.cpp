#include <Geode/Geode.hpp>
#include <Geode/modify/CCDirector.hpp>

using namespace geode::prelude;

class $modify(MyCCDirector, CCDirector) {
    void drawScene() {
        // 1. Le jeu dessine d'abord l'image normale
        CCDirector::drawScene();

        // 2. On récupère la valeur de ta barre
        double darknessValue = Mod::get()->getSettingValue<double>("screen-darkness");
        
        if (darknessValue <= 0.0) return;

        // 3. On dessine avec le BON nom de fonction : ccDrawSolidRect
        float alpha = static_cast<float>(darknessValue);
        ccDrawSolidRect(
            ccp(0, 0), 
            CCDirector::sharedDirector()->getWinSize(), 
            ccc4f(0.0f, 0.0f, 0.0f, alpha)
        );
    }
};

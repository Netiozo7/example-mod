#include <Geode/Geode.hpp>
#include <Geode/modify/CCDirector.hpp>

using namespace geode::prelude;

class $modify(MyCCDirector, CCDirector) {
    void drawScene() {
        // 1. On laisse le jeu dessiner l'image normale d'abord
        CCDirector::drawScene();

        // 2. On récupère la valeur de ta barre
        double darknessValue = Mod::get()->getSettingValue<double>("screen-darkness");
        
        // Si la barre est tout à gauche (0.0), on ne dessine rien pour économiser les performances
        if (darknessValue <= 0.0) return;

        GLubyte opacity = static_cast<GLubyte>(darknessValue * 255.0);

        // 3. On dessine un rectangle noir transparent directement par-dessus TOUTE la fenêtre
        // ccc4f utilise des valeurs entre 0.0f et 1.0f
        float alpha = static_cast<float>(darknessValue);
        
        // On utilise la fonction de dessin native de Cocos2d pour dessiner un carré géant
        ccDrawFilledRect(ccp(0, 0), CCDirector::sharedDirector()->getWinSize(), ccc4f(0.0f, 0.0f, 0.0f, alpha));
    }
};

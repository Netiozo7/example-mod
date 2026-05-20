#include <Geode/Geode.hpp>
#include <Geode/modify/CCDirector.hpp>

using namespace geode::prelude;

class $modify(MyCCDirector, CCDirector) {
    void drawScene() {
        // 1. On laisse le jeu tout dessiner normalement
        CCDirector::drawScene();

        // 2. On récupère la valeur de ta barre
        double darknessValue = Mod::get()->getSettingValue<double>("screen-darkness");
        if (darknessValue <= 0.0) return;

        // 3. LA SOLUTION : On utilise les commandes OpenGL natives pour forcer le dessin
        // On active le blending (la transparence)
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // On dessine notre rectangle
        float alpha = static_cast<float>(darknessValue);
        ccDrawSolidRect(
            ccp(0, 0), 
            CCDirector::sharedDirector()->getWinSize(), 
            ccc4f(0.0f, 0.0f, 0.0f, alpha)
        );
    }
};

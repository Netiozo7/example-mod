#include <Geode/Geode.hpp>
#include <Geode/modify/CCDirector.hpp>

using namespace geode::prelude;

// On crée un pointeur persistant pour notre filtre
static CCLayerColor* g_brightnessOverlay = nullptr;

class $modify(MyCCDirector, CCDirector) {
    void pushScene(CCScene* scene) {
        CCDirector::pushScene(scene);
        this->updateOverlay(scene);
    }

    void replaceScene(CCScene* scene) {
        CCDirector::replaceScene(scene);
        this->updateOverlay(scene);
    }

    // Fonction maison pour déplacer le filtre sur la nouvelle scène active
    void updateOverlay(CCScene* nextScene) {
        if (!nextScene) return;

        // 1. On récupère la valeur de la barre
        double darknessValue = Mod::get()->getSettingValue<double>("screen-darkness");
        GLubyte opacity = static_cast<GLubyte>(darknessValue * 255.0);

        // 2. Si le filtre n'existe pas encore ou a été perdu, on le recrée proprement
        if (!g_brightnessOverlay || !g_brightnessOverlay->getParent()) {
            g_brightnessOverlay = CCLayerColor::create(ccc4(0, 0, 0, opacity));
            g_brightnessOverlay->setZOrder(999999); // Tout devant
            g_brightnessOverlay->setTouchEnabled(false);
            g_brightnessOverlay->retain(); // On empêche sa destruction en mémoire
        } else {
            // Si le filtre existe déjà, on le détache de l'ancienne scène mourante
            g_brightnessOverlay->removeFromParentAndCleanup(false);
            g_brightnessOverlay->setOpacity(opacity);
        }

        // 3. On l'injecte au premier plan de la toute nouvelle scène (fonctionne pour TOUT, même PlayLayer)
        nextScene->addChild(g_brightnessOverlay);
    }
};

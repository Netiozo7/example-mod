#include <Geode/Geode.hpp>

using namespace geode::prelude;

// On s'enregistre au démarrage du mod (zéro modification de scènes !)
$execute {
    // 1. On récupère la valeur de ta barre
    double darknessValue = Mod::get()->getSettingValue<double>("screen-darkness");
    GLubyte opacity = static_cast<GLubyte>(darknessValue * 255.0);

    // 2. On crée notre calque noir géant
    auto brightnessOverlay = CCLayerColor::create(ccc4(0, 0, 0, opacity));
    brightnessOverlay->setZOrder(99999);
    brightnessOverlay->setTouchEnabled(false);
    
    // On lui donne un identifiant pour le retrouver si besoin
    brightnessOverlay->setID("global-brightness-overlay");

    // 3. LA MAGIE : On le colle sur la scène de base de tout le moteur de jeu (CCEGLView)
    // De cette façon, il flotte au-dessus du jeu sans toucher aux scènes de GD !
    if (auto runningScene = CCDirector::sharedDirector()->getRunningScene()) {
        runningScene->addChild(brightnessOverlay);
    }

    // 4. On s'assure qu'il reste là même quand on change d'écran
    // (Geode s'occupe de garder les nœuds persistants en vie)
    brightnessOverlay->retain();
}

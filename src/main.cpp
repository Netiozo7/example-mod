#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        // 128 partout = luminosité baissée de moitié (mode sombre)
        ccColor3B darkColor = {128, 128, 128};

        // On applique la couleur au fond si possible
        if (auto rgbaNode = dynamic_cast<CCRGBAProtocol*>(this)) {
            rgbaNode->setColor(darkColor);
        }

        // On parcourt tous les éléments de l'écran en toute sécurité
        for (auto child : CCArrayExt<CCNode*>(this->getChildren())) {
            if (auto rgbaChild = dynamic_cast<CCRGBAProtocol*>(child)) {
                rgbaChild->setColor(darkColor);
            }
        }

        return true;
    }
};

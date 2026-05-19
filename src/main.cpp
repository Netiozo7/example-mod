#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        ccColor3B darkColor = {128, 128, 128};

        if (auto rgbaNode = dynamic_cast<CCRGBAProtocol*>(this)) {
            rgbaNode->setColor(darkColor);
        }

        for (auto child : CCArrayExt<CCNode*>(this->getChildren())) {
            if (auto rgbaChild = dynamic_cast<CCRGBAProtocol*>(child)) {
                rgbaChild->setColor(darkColor);
            }
        }

        return true;
    }
};

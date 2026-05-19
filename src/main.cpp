#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        // 128 partout = luminosité baissée de moitié (mode sombre)
        GLubyte r = 128; 
        GLubyte g = 128;
        GLubyte b = 128;

        this->setColor({r, g, b});

        for (auto child : CCArrayExt<CCNode*>(this->getChildren())) {
            child->setColor({r, g, b});
        }

        return true;
    }
};



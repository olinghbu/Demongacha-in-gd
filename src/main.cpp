#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

static constexpr auto DEMONGACHA_URL = "https://demongacha.com";

class $modify(DGMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // Icono: "DG" encima de un círculo rosa, como los botones de abajo del menú
        auto label = CCLabelBMFont::create("DG", "bigFont.fnt");
        auto spr = CircleButtonSprite::create(label, CircleBaseColor::Pink);

        auto btn = CCMenuItemSpriteExtra::create(
            spr, this, menu_selector(DGMenuLayer::onDemonGacha)
        );
        btn->setID("demongacha-button"_spr);

        if (auto menu = this->getChildByID("bottom-menu")) {
            menu->addChild(btn);
            menu->updateLayout();
        } else {
            // Por si otro mod cambia el menú: lo ponemos abajo a la izquierda
            auto menu = CCMenu::create();
            menu->setID("demongacha-menu"_spr);
            menu->setPosition({ 35.f, 35.f });
            menu->addChild(btn);
            this->addChild(menu);
        }
        return true;
    }

    void onDemonGacha(CCObject*) {
        createQuickPopup(
            "DemonGacha",
            "¿Abrir <cp>demongacha.com</c> en el navegador?",
            "No", "Abrir",
            [](FLAlertLayer*, bool abrir) {
                if (abrir) {
                    web::openLinkInBrowser(DEMONGACHA_URL);
                }
            }
        );
    }
};

//
// Created by tv on 13.11.23.
//

#include "DirectoryMenu.h"
#include "Shared/Core/Logging.h"
#include<Internal/silverlight.h>

#include <utility>

namespace Menus {

    void DirectoryMenu::draw() {
        for (unsigned int i = 0; i < m_menuItems.size(); i++) {
            std::string text = "";

            if (i == m_selectionIdx)
                text += ">";
            else
                text += " ";

            text += m_menuItems[i]->getDisplayText();
            text += "\n";

            silverlightInstance->m_renderer.drawText(text);
        }

		std::shared_ptr<Menus::DirectoryMenuItem> selectedMenuItem = this->m_menuItems[this->m_selectionIdx];

		Menus::DirectoryMenuItem* selectedMenuItemRef = selectedMenuItem.get();

		if (!selectedMenuItemRef) return;

		Menus::PatchModuleItem* selectedPatchModuleItem = dynamic_cast<Menus::PatchModuleItem*>(selectedMenuItemRef);
		Menus::UpdateModuleItem* selectedUpdateModuleItem = dynamic_cast<Menus::UpdateModuleItem*>(selectedMenuItemRef);

		std::string helpText = {};

		if (selectedPatchModuleItem) {
			helpText = selectedPatchModuleItem->m_module->helpText();
		}
		if (selectedUpdateModuleItem) {
			helpText = selectedUpdateModuleItem->m_module->helpText();
		}

		if (!helpText.empty()) {
        	silverlightInstance->m_renderer.drawText("Module Help: " + helpText);
		}
    }

    void DirectoryMenu::click() {
        m_menuItems[m_selectionIdx]->click();
    }

    void DirectoryMenu::cursorUp() {
        if (m_selectionIdx != 0)
            m_selectionIdx -= 1;
        else
            m_selectionIdx = m_menuItems.size() - 1;
    }

    void DirectoryMenu::cursorDown() {
        if (m_selectionIdx != m_menuItems.size() - 1)
            m_selectionIdx += 1;
        else
            m_selectionIdx = 0;
    }

    Menus::SubdirectoryItem::SubdirectoryItem(std::string name, std::shared_ptr<Menu> menu) : m_menuName(name) {
        m_menu = menu;
    }

    void SubdirectoryItem::click() {
        silverlightInstance->m_menu = m_menu;
    }

    std::string SubdirectoryItem::getDisplayText() {
        return m_menuName;
    }

    BoolItem::BoolItem(std::string name, bool &value) : m_name(std::move(name)), m_value(value) {}

    void BoolItem::click() {
        m_value ^= true;
    }

    std::string BoolItem::getDisplayText() {
        return m_name + ": " + (m_value ? "true" : "false");
    }

    ButtonItem::ButtonItem(std::string text, std::function<void()> func) : m_text(std::move(text)),
                                                                           m_func(std::move(func)) {}

    void ButtonItem::click() {
        m_func();
    }

    std::string ButtonItem::getDisplayText() {
        return m_text;
    }

    UpdateModuleItem::UpdateModuleItem(const char *name, Modules::UpdateModule *module) : m_name(name),
                                                                                          m_module(module) {}

    void UpdateModuleItem::click() {
        m_module->toggle();
    }

    std::string UpdateModuleItem::getDisplayText() {
        return "[U] " + std::string(m_name) + ": " + (m_module->m_enabled ? "On" : "Off");
    }

    UpdateModuleItem::UpdateModuleItem(const char *display, const char *name) :
            UpdateModuleItem(display,
                             [](const char *name) -> Modules::UpdateModule * {
                                 CAFEINFO("Attempting to find Module: " + std::string(name));
                                 return silverlightInstance->m_moduleStates.getUpdateModule(name);
                             }(name)) {}

    PatchModuleItem::PatchModuleItem(const char *name, Modules::PatchModule *module) : m_name(name),
                                                                                       m_module(module) {}

    void PatchModuleItem::click() {
        m_module->toggle();
    }

    std::string PatchModuleItem::getDisplayText() {
        return "[P] " + m_name + ": " + (m_module->m_enabled ? "On" : "Off");
    }

    PatchModuleItem::PatchModuleItem(const char *display, const char *name) :
            PatchModuleItem(display,
                            [](const char *name) -> Modules::PatchModule * {
                                CAFEINFO("Attempting to find Module: " + std::string(name));
                                return silverlightInstance->m_moduleStates.getPatchModule(name);
                            }(name)) {}

    void DirectoryMenuItem::update() {

    }

    DropDownSelectionItem::DropDownSelectionItem(std::string name, const std::vector<DropDownItem> &items) : m_name(
            name),
                                                                                                             m_items(items) {

    }

    void DropDownSelectionItem::click() {
        m_dropdownEnabled = true;
        silverlightInstance->m_menuControl = false;
    }

    void DropDownSelectionItem::update() {

    }

    std::string DropDownSelectionItem::getDisplayText() {
        return "NO";
    }
} // Menu

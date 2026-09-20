//
// Created by tv on 13.11.23.
//

#pragma once

#include<vector>
#include<Internal/silverlight.h>
#include<functional>

namespace Menus {
    class DirectoryMenuItem {
    public:

        virtual void click() = 0;

        //Note: only gets called if it is actively getting displayed
        virtual void update();

        virtual std::string getDisplayText() = 0;
    };


    class SubdirectoryItem : public DirectoryMenuItem {
    public:
        SubdirectoryItem(std::string name, std::shared_ptr<Menu> menu);

        void click() override;

        std::string getDisplayText() override;

    private:
        const std::string m_menuName;
        std::shared_ptr<Menu> m_menu;
    };

    class BoolItem : public DirectoryMenuItem {
    public:
        BoolItem(std::string name, bool &value);

        void click() override;

        std::string getDisplayText() override;

        const std::string m_name;
        bool &m_value;
    };

    struct DropDownItem {
        std::string display;
        unsigned int index;
    };

    class DropDownSelectionItem : public DirectoryMenuItem {
    public:
        DropDownSelectionItem(std::string name, const std::vector<DropDownItem> &items);

        void click() override;

        void update() override;

        std::string getDisplayText() override;

        const std::string m_name;
        bool m_dropdownEnabled;
        const std::vector<DropDownItem> &m_items;
    };

    class UpdateModuleItem : public DirectoryMenuItem {
    public:

        UpdateModuleItem(const char *display, const char *name);

        UpdateModuleItem(const char *name, Modules::UpdateModule *module);

        void click() override;

        std::string getDisplayText() override;

        const char *m_name;
        Modules::UpdateModule *m_module;
    };

    class PatchModuleItem : public DirectoryMenuItem {
    public:
        PatchModuleItem(const char *display, const char *name);

        PatchModuleItem(const char *name, Modules::PatchModule *module);

        void click() override;

        std::string getDisplayText() override;

        const std::string m_name;
        Modules::PatchModule *m_module;
    };

    class ButtonItem : public DirectoryMenuItem {
    public:
        ButtonItem(std::string name, std::function<void()> func);

        void click() override;

        std::string getDisplayText() override;

        const std::string m_text;
    private:
        std::function<void()> m_func;
    };

    class DirectoryMenu : public Menu {
    public:
        void draw() override;

        void click() override;

        void cursorUp() override;

        void cursorDown() override;

        unsigned int m_selectionIdx = 0;
        std::vector<std::shared_ptr<DirectoryMenuItem>> m_menuItems;
    };

} // Menu

#include"SubdirectoryMenu.inl"
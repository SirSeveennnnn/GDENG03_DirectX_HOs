#pragma once
#include <string>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

using namespace std;

class UIManager;

class AUIScreen
{

protected:
    string name;

    AUIScreen(string name);
    ~AUIScreen();

    string getName();
    virtual void DrawUI() = 0;

    friend class UIManager;

};





inline string AUIScreen::getName()
{
    return name;
}

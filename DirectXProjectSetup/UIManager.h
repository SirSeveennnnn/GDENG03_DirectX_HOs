#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "Windows.h"
#include "AUIScreen.h"

#include "UI_MenuToolBar.h"

using namespace std;



class UIManager
{
public :
    static UIManager* getInstance();
    static void initialize(HWND windowHandle);
    static void destroy();

    void drawAllUI();
    void renderUI();
    static const int WINDOW_WIDTH = 1440;
    static const int WINDOW_HEIGHT = 900;

private:
    UIManager();
    ~UIManager();

    void CreateUI();

    UIManager(UIManager const&) {};
    UIManager& operator=(UIManager const&) {};
    static UIManager* sharedInstance;

    vector<AUIScreen*> UIList;
    unordered_map<string, AUIScreen*> UITable;

    
};


#include "UIManager.h"
#include "GraphicsEngine.h"

#include "UI_MenuToolBar.h"
#include "UI_SceneOutliner.h"
#include  "UI_InspectorWindow.h"
#include "UI_EngineProfiler.h"

UIManager* UIManager::sharedInstance = nullptr;

UIManager* UIManager::getInstance()
{
    return sharedInstance;
}

void UIManager::initialize(HWND windowHandle)
{
  
    sharedInstance = new UIManager();
    
    //IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(windowHandle);
    ImGui_ImplDX11_Init(GraphicsEngine::get()->getDevice(), GraphicsEngine::get()->getD3D11DeviceContext());

    UI_MenuToolBar* toolbar = new UI_MenuToolBar("Toolbar");
    sharedInstance->UIList.push_back(toolbar);

    UI_SceneOutliner* sceneOutliner = new UI_SceneOutliner("Scene Outliner");
    sharedInstance->UIList.push_back(sceneOutliner);

    UI_InspectorWindow* inspector = new UI_InspectorWindow("Inspector");
    sharedInstance->UIList.push_back(inspector);

    UI_EngineProfiler* engineProfiler = new UI_EngineProfiler("Scene Outliner");
    sharedInstance->UIList.push_back(engineProfiler);
   
}

void UIManager::destroy()
{
}

void UIManager::drawAllUI()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    for (int i = 0; i < UIList.size(); i++)
    {
        this->UIList[i]->DrawUI();
    }

    
}

void UIManager::renderUI()
{
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

void UIManager::CreateUI()
{
    
}
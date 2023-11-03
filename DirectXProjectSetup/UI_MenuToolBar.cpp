#include "UI_MenuToolBar.h"

#include "GameObjectManager.h"

UI_MenuToolBar::UI_MenuToolBar(std::string name) : AUIScreen(name)
{
    
}

bool test;
void UI_MenuToolBar::DrawUI()
{
    ImGui::BeginMainMenuBar();


    if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("New"))
        {
            
        }
        if (ImGui::MenuItem("Save"))
        {
            
        }
        if (ImGui::MenuItem("Open"))
        {
            
        }
        if (ImGui::MenuItem("Exit"))
        {
            
        }
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Game Object")) {

        if (ImGui::MenuItem("Create Cube")) {
            GameObjectManager::getInstance()->CreateObject(TypeCube);
        }

        if (ImGui::MenuItem("Create Sphere"))
        {
            
        }

        if (ImGui::MenuItem("Create Plane")) {
            GameObjectManager::getInstance()->CreateObject(TypePlane);
        }
        if (ImGui::BeginMenu("Create Light")) {
            if (ImGui::MenuItem("Point Light")) {}
            ImGui::EndMenu();
        }

        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
}

#include "UI_InspectorWindow.h"

#include "GameObjectManager.h"

UI_InspectorWindow::UI_InspectorWindow(std::string name) : AUIScreen::AUIScreen(name)
{
    
}

void UI_InspectorWindow::DrawUI(){
    ImGuiWindowFlags windowFlags = 0;

    ImGui::Begin("Inspector Window", NULL, windowFlags);
    ImGui::SetWindowSize(ImVec2(300, 500));
    if (!GameObjectManager::getInstance()->GetSelectedObject()) {
        ImGui::TextWrapped("No object selected. Select an object from the scene.");
    }
    else {
        GameObject* selectedObject = GameObjectManager::getInstance()->GetSelectedObject();
        ImGui::Text("Selected Object:");
        ImGui::SameLine();
        ImGui::Text(selectedObject->getName().c_str());
        ImGui::Separator();

        float objectPos[3] = {selectedObject->getLocalPosition().m_x, selectedObject->getLocalPosition().m_y, selectedObject->getLocalPosition().m_z};
        ImGui::DragFloat3("Position", objectPos, 1);

        float objectRot[3] = { selectedObject->getLocalRotation().m_x, selectedObject->getLocalRotation().m_y, selectedObject->getLocalRotation().m_z };
        ImGui::DragFloat3("Rotation", objectRot, 1);

        float objectScale[3] = { selectedObject->getLocalScale().m_x, selectedObject->getLocalScale().m_y, selectedObject->getLocalScale().m_z };
        ImGui::DragFloat3("Scale", objectScale, 1);

    }
    

    ImGui::End();
}
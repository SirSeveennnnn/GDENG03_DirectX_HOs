#include "UI_SceneOutliner.h"

#include <vector>

#include "GameObjectManager.h"

UI_SceneOutliner::UI_SceneOutliner(std::string name) : AUIScreen(name)
{

}

void UI_SceneOutliner::DrawUI()
{
    ImGuiWindowFlags windowFlags = 0;
    ImGui::Begin("Scene Outliner", NULL, windowFlags);
    ImGui::SetWindowSize(ImVec2(210,500));
   

    
    vector<GameObject*> gameObjectList = GameObjectManager::getInstance()->GetAllGameObjects();
    for (int i = 0; i < gameObjectList.size(); i++) {
        if (gameObjectList[i] == GameObjectManager::getInstance()->GetSelectedObject()) {
            if (ImGui::Button(gameObjectList[i]->getName().c_str(), ImVec2(200, 20))) {
                //GameObjectManager::getInstance()->deselectObject();
            }
        }

        else {
            if (ImGui::Button(gameObjectList[i]->getName().c_str(), ImVec2(200, 20))) {
                GameObjectManager::getInstance()->SelectGameObject(gameObjectList[i]);
            }
        }
    }
    
    ImGui::End();
}

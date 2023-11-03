#pragma once
#pragma once
#include"GameObject.h"
#include<string>
#include<vector>
#include<unordered_map>
#include"VertexShader.h"
#include"PixelShader.h"


enum GameObjectType
{
    TypeCube,
    TypePlane
};

class GameObjectManager
{
public:

    static GameObjectManager* getInstance();
    static void Initialize(float width, float height);

    std::vector<GameObject*> GetAllGameObjects();
    int GetObjectCount();
    void Update(Matrix4x4 viewMatrix, float animMultiplier);
    void DrawObjects();
    void AddObject(GameObject* gameObject);
    void CreateObject(GameObjectType type);
    void DeleteObject(GameObject* gameObject);

    void SelectGameObject(GameObject* gameObject);
    void DeselectObject();
    GameObject* GetSelectedObject();
   

private:
    GameObjectManager();
    ~GameObjectManager();

    GameObjectManager(GameObjectManager const&) {};
    GameObjectManager& operator =(GameObjectManager const&) {};
    static GameObjectManager* instance;

    std::vector<GameObject*> gameObjectList;
    std::unordered_map<std::string, GameObject*> mGameObjectTable;

    GameObject* selectedObject = nullptr;

    float windowWidth;
    float windowHeight;
};


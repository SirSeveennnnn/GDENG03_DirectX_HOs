#include"GameObjectManager.h"
#include"EngineTime.h"
#include"Cube.h"
//#include"APlane.h"
#include"GraphicsEngine.h"
#include<iostream>

GameObjectManager* GameObjectManager::instance = nullptr;

void GameObjectManager::Update(Matrix4x4 viewMatrix, float animMultiplier)
{
    for(int i = 0; i < gameObjectList.size(); i++)
    {
        gameObjectList[i]->OnUpdate(viewMatrix, animMultiplier);
    }
}

void GameObjectManager::DrawObjects()
{
    for (int i = 0; i < gameObjectList.size(); i++)
    {
        gameObjectList[i]->Draw();
    }
}

GameObjectManager* GameObjectManager::getInstance() {
    return instance;
}

void GameObjectManager::Initialize(float width, float height) {
    instance = new GameObjectManager();
    instance->windowWidth = width;
    instance->windowHeight = height;
}

std::vector<GameObject*> GameObjectManager::GetAllGameObjects()
{
    return gameObjectList;
}

int GameObjectManager::GetObjectCount()
{
    return gameObjectList.size();
}

void GameObjectManager::AddObject(GameObject* gameObject)
{
    gameObjectList.push_back(gameObject);
}

void GameObjectManager::CreateObject(GameObjectType type)
{
    if (type == TypeCube)
    {
        Cube* cube = new Cube("Cube", windowWidth, windowHeight);
        cube->setPosition(0, 0, 0);
        cube->setRotation(0, 0, 0);
        cube->setScale(1, 1, 1);
        gameObjectList.push_back(cube);
    }
    else if (type == TypePlane)
    {
        Cube* cube = new Cube("Plane", windowWidth, windowHeight);
        cube->setPosition(0, -1, 0);
        cube->setRotation(0, 0, 0);
        cube->setScale(5, 0.001f, 5);
        gameObjectList.push_back(cube);
    }
}

void GameObjectManager::DeleteObject(GameObject* gameObject)
{
    gameObjectList.erase(std::remove(gameObjectList.begin(), gameObjectList.end(), gameObject), gameObjectList.end());
    gameObjectList.shrink_to_fit();
    delete gameObject;
}

void GameObjectManager::SelectGameObject(GameObject* gameObject)
{
    selectedObject = gameObject;
}

void GameObjectManager::DeselectObject()
{
    selectedObject = nullptr;
}

GameObject* GameObjectManager::GetSelectedObject()
{
    return selectedObject;
}

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}


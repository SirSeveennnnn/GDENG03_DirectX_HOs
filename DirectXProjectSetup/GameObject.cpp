#include "GameObject.h"
#include <iostream>

using namespace std;

GameObject::GameObject()
{
    cout << "GameObject Init" << endl;
 
    SetPosition(Vector3D(0, 0, 0));
    SetScale(Vector3D(1, 1, 1));
    //setRotationX(0);
    //setRotationY(0);
    //setRotationZ(0);

    //cout << "Gameobject Pos: " << position.m_x << ", " << position.m_y << ", " << position.m_z << endl;
}

GameObject::~GameObject()
{
}

void GameObject::SetPosition(Vector3D pos)
{
    Matrix4x4 temp;
    temp.setTranslation(pos);
    transform *= temp;
    this->position = pos;
}

void GameObject::SetScale(Vector3D scale)
{
    Matrix4x4 temp;
    temp.setScale(scale);
    transform *= temp;
    this->scale = scale;
}

void GameObject::setRotationX(float x)
{
    Matrix4x4 temp;
    temp.setRotationZ(x);
    transform *= temp;
    rotation.m_x = x;
}

void GameObject::setRotationY(float y)
{
    Matrix4x4 temp;
    temp.setRotationY(y);
    transform *= temp;
    rotation.m_y = y;
}

void GameObject::setRotationZ(float z)
{
    Matrix4x4 temp;
    temp.setRotationZ(z);
    transform *= temp;
    rotation.m_y = z;
}

void GameObject::setIdentity()
{
    transform.setIdentity();
}



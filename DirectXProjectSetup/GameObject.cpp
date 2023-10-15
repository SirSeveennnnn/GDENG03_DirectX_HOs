#include "GameObject.h"

GameObject::GameObject(string name)
{
    this->name = name;
    this->localRotation = Vector3D::zeros();
    this->localPosition = Vector3D::zeros();
    this->localScale = Vector3D::ones();
}

GameObject::~GameObject()
{
}

void GameObject::setPosition(float x, float y, float z)
{
    this->localPosition = Vector3D(x, y, z);
}

void GameObject::setPosition(Vector3D pos)
{
    this->localPosition = pos;
}

Vector3D GameObject::getLocalPosition()
{
    return this->localPosition;
}

void GameObject::setScale(float x, float y, float z)
{
    this->localScale = Vector3D(x, y, z);
}

void GameObject::setScale(Vector3D scale)
{
    this->localScale = scale;
}

void GameObject::setRotation(float x, float y, float z)
{
    this->localRotation = Vector3D(x, y, z);
}

void GameObject::setRotation(Vector3D rot)
{
    this->localRotation = rot;
}

Vector3D GameObject::getLocalRotation()
{
    return this->localRotation;
}

Vector3D GameObject::getLocalScale()
{
    return this->localScale;
}

string GameObject::getName()
{
    return this->name;
}
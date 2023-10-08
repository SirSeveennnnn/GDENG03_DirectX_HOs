#pragma once
#include "Vector3D.h"
#include "Matrix4x4.h"

class GameObject
{

public:
    GameObject();
    ~GameObject();

    void SetPosition(Vector3D pos);
    void SetScale(Vector3D scale);
    void setRotationX(float x);
    void setRotationY(float y);
    void setRotationZ(float z);
    void setIdentity();

public:
    Vector3D position;
    Vector3D scale;
    Vector3D rotation;

protected:
    Matrix4x4 transform;
};


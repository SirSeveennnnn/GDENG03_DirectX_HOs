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

void GameObject::OnUpdate(Matrix4x4 viewMatrix, float animMultiplier)
{
}

void GameObject::Draw()
{
}

Vector3D GameObject::getLocalScale()
{
    return this->localScale;
}

string GameObject::getName()
{
    return this->name;
}

void GameObject::recomputeMatrix(float matrix[16])
{
    float matrix4x4[4][4];
    matrix4x4[0][0] = matrix[0];
    matrix4x4[0][1] = matrix[1];
    matrix4x4[0][2] = matrix[2];
    matrix4x4[0][3] = matrix[3];

    matrix4x4[1][0] = matrix[4];
    matrix4x4[1][1] = matrix[5];
    matrix4x4[1][2] = matrix[6];
    matrix4x4[1][3] = matrix[7];

    matrix4x4[2][0] = matrix[8];
    matrix4x4[2][1] = matrix[9];
    matrix4x4[2][2] = matrix[10];
    matrix4x4[2][3] = matrix[11];

    matrix4x4[3][0] = matrix[12];
    matrix4x4[3][1] = matrix[13];
    matrix4x4[3][2] = matrix[14];
    matrix4x4[3][3] = matrix[15];

    Matrix4x4 newMatrix; newMatrix.setMatrixByFloat(matrix4x4);
    Matrix4x4 scaleMatrix; scaleMatrix.setScale(this->localScale);
    Matrix4x4 transMatrix; transMatrix.setTranslation(this->localPosition);
    this->localMatrix = scaleMatrix.multiplyTo(transMatrix.multiplyTo(newMatrix));
    this->setPosition(newMatrix.m_mat[3][0], newMatrix.m_mat[3][1], newMatrix.m_mat[3][2]);
}

float* GameObject::getPhysicsLocalMatrix()
{

    Matrix4x4 matrix;
    matrix.setIdentity();
    matrix.setScale(this->getLocalScale());

    Matrix4x4 rotZ;
    rotZ.setIdentity();
    rotZ.setRotationZ(localRotation.m_z);
    matrix *= rotZ;

    Matrix4x4 rotY;
    rotY.setIdentity();
    rotY.setRotationY(localRotation.m_y);
    matrix *= rotY;

    Matrix4x4 rotX;
    rotX.setIdentity();
    rotX.setRotationX(localRotation.m_x);
    matrix *= rotX;



    matrix.setTranslation(this->getLocalPosition());


    return matrix.getMatrix();
}
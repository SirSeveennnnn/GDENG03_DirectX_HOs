#pragma once
#include "ConstantBuffer.h"
#include "GameObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "EngineTime.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

class Cube : public GameObject
{

public:
    Cube(string name, float screenW, float screenH);
    ~Cube();

    void OnUpdate(Matrix4x4 viewMatrix, float animMultiplier);
    void Draw();
    void SetAnimationSpeed(float speed);

private:
    VertexBuffer* m_vb;
    IndexBuffer* m_ib;
    VertexShader* m_vs;
    PixelShader* m_ps;
    ConstantBuffer* m_cb;

    float animationSpeed = 1.0f;

    //temp
    float screenHeight = 0;
    float screenWidth = 0;

    float deltaScale;

};
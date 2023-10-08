#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Cube.h"
#include <vector>

class AppWindow : public Window
{
public:
    AppWindow();

    void updateQuadPosition();

    ~AppWindow();

    // Inherited via Window
    virtual void onCreate() override;
    virtual void onUpdate() override;
    virtual void onDestroy() override;
private:
    vector<Cube*> cubeList;

    SwapChain* m_swap_chain;
    VertexBuffer* m_vb;
    VertexShader* m_vs;
    PixelShader* m_ps;
    ConstantBuffer* m_cb;
    IndexBuffer* m_ib;
private:
    long m_old_delta;
    long m_new_delta;
    float m_delta_time;

    float m_delta_pos;
    float m_delta_scale;
    float m_delta_rot;
};
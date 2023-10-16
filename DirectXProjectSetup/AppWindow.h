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

#include "InputListener.h"

class AppWindow : public Window, public InputListener
{
public:
    AppWindow();

    void UpdateCamera();

    ~AppWindow();

    // Inherited via Window
    virtual void onCreate() override;
    virtual void onUpdate() override;
    virtual void onDestroy() override;


    virtual void onKeyDown(int key) override;
    virtual void onKeyUp(int key) override;

    virtual void onMouseMove(const Point deltaPos);

    virtual void onLeftMouseDown(const Point deltaPos);
    virtual void onLeftMouseUp(const Point deltaPos);

    virtual void onRightMouseDown(const Point deltaPos);
    virtual void onRightMouseUp(const Point deltaPos);
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

    float m_rot_x = 0.0f;
    float m_rot_y = 0.0f;

    float m_scale_cube = 1;
    float m_forward = 0.0f;
    float m_rightward = 0.0f;
    Matrix4x4 m_world_cam;
    Vector3D cameraRotation;
    Vector3D cameraPosition;

    float animMultiplier;
};


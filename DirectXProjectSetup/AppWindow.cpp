#include "AppWindow.h"
#include <Windows.h>

#include "InputSystem.h"
#include "MathUtils.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "UIManager.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"


struct vertex
{
    Vector3D position;
    Vector3D color;
    Vector3D color1;
};


__declspec(align(16))
struct constant
{
    Matrix4x4 m_world;
    Matrix4x4 m_view;
    Matrix4x4 m_proj;
    unsigned int m_time;
};


AppWindow::AppWindow()
{
}

void AppWindow::UpdateCamera()
{
    m_world_cam.setIdentity();


    Matrix4x4 rotX;
    rotX.setIdentity();
    rotX.setRotationX(cameraRotation.m_x);
    m_world_cam *= rotX;

    Matrix4x4 rotY;
    rotY.setIdentity();
    rotY.setRotationY(cameraRotation.m_y);
    m_world_cam *= rotY;

    cameraPosition = cameraPosition + m_world_cam.getZDirection() * (m_forward * 0.1f);
    cameraPosition = cameraPosition + m_world_cam.getXDirection() * (m_rightward * 0.1f);


    m_world_cam.setTranslation(cameraPosition);
   

    m_world_cam.inverse();

}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
    Window::onCreate();
    GraphicsEngine::get()->init();
    m_swap_chain = GraphicsEngine::get()->createSwapChain();

    EngineTime::initialize();
    InputSystem::initialize();
    InputSystem::getInstance()->addListener(this);


    RECT rc = this->getClientWindowRect();
    m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);


    
    for (int i = 0; i < 50; i++) {
        float x = MathUtils::randomFloat(-0.5f, 0.5f);
        float y = MathUtils::randomFloat(-0.5f, 0.5f);
        float z = MathUtils::randomFloat(-0.5f, 0.5f);

        Cube* cube = new Cube(std::to_string(i), (this->getClientWindowRect().right - this->getClientWindowRect().left), (this->getClientWindowRect().bottom - this->getClientWindowRect().top));
        cube->SetAnimationSpeed(MathUtils::randomFloat(5, 10));
        cube->setPosition(Vector3D(x, y, z));
        cube->setScale(Vector3D(0.25, 0.25, 0.25));
        this->cubeList.push_back(cube);
    }
    


    m_world_cam.setIdentity();
    cameraPosition.m_x = 0;
    cameraPosition.m_y = 0;
    cameraPosition.m_z = -2;

    UIManager::initialize(this->m_hwnd);
 
}

void AppWindow::onUpdate()
{
    /*
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (show_demo_window)
    {
        ImGui::ShowDemoWindow();
    }
   

    static float f = 0.0f;
    static int counter = 0;

    ImGuiWindowFlags flag = 64;
    ImGui::Begin("Scene Settings", 0, flag);
    ImGui::Checkbox("Demo Window", &show_demo_window);

    ImGui::ColorEdit3("clear color", (float*)&clear_color); 

    if (animation)
    {
        if (ImGui::Button("Pause Animation"))
        {
            animation = !animation;
            animMultiplier = 0;
        }
    }
    else
    {
        if (ImGui::Button("Start Animation"))
        {
            animation = !animation;
            animMultiplier = 1;
        }
    }

    ImGui::End();
    */
    

    InputSystem::getInstance()->update();

    Window::onUpdate();
    //CLEAR THE RENDER TARGET 
    GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,clear_color.x, clear_color.y, clear_color.z, 1);
    //SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
    RECT rc = this->getClientWindowRect();
    GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

    UpdateCamera();

    UIManager::getInstance()->drawAllUI();

    for (Cube* cube : cubeList)
    {
        cube->OnUpdate(m_world_cam, animMultiplier);
        cube->Draw();
    }

   

    //ImGui::Render();
    //ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    UIManager::getInstance()->renderUI();
  
    m_swap_chain->present(true);

    m_old_delta = m_new_delta;
    m_new_delta = ::GetTickCount();

    m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;
}

void AppWindow::onDestroy()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    Window::onDestroy();
    m_vb->release();
    m_ib->release();
    m_cb->release();    
    m_swap_chain->release();
    m_vs->release();
    m_ps->release();
    GraphicsEngine::get()->release();
}

void AppWindow::onKeyDown(int key)
{
    
    //cout << "onkeydown:\n";
    if (key == 'W')
	{
        m_forward = 1.0f;
        //animMultiplier = 1.0f;
	}
	else if (key == 'S')
	{
        //animMultiplier = -1.0f;
        m_forward = -1.0f;
	}
	else if (key == 'A')
	{
        m_rightward = -1.0f;
	}
	else if (key == 'D')
	{
	    m_rightward = 1.0f;
	}

}


void AppWindow::onKeyUp(int key)
{
    m_forward = 0.0f;
    m_rightward = 0.0f;
    animMultiplier = 0.0f;
}

void AppWindow::onMouseMove(const Point deltaPos)
{
    //cout << " mouse moved: " << deltaPos.getX() << ", " << deltaPos.getY() << "\n";
    //cout << " camera rot: " << cameraRotation.m_x << ", " << cameraRotation.m_y << "\n";
    int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
    int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);



    m_rot_x += (deltaPos.getY() - (height / 2.0f)) * m_delta_time * 0.1f;
    m_rot_y += (deltaPos.getX() - (width / 2.0f)) * m_delta_time * 0.1f;

    if (rotateCam)
    {
        cameraRotation.m_x += deltaPos.getY() * 0.5f * m_delta_time;
        cameraRotation.m_y += deltaPos.getX() * 0.5f * m_delta_time;
    }

}

void AppWindow::onLeftMouseDown(const Point deltaPos)
{
   
}

void AppWindow::onLeftMouseUp(const Point deltaPos)
{
   
}

void AppWindow::onRightMouseDown(const Point deltaPos)
{
    rotateCam = true;
}

void AppWindow::onRightMouseUp(const Point deltaPos)
{
    rotateCam = false;
}
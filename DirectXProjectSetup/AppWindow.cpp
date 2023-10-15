#include "AppWindow.h"
#include <Windows.h>

#include "InputSystem.h"
#include "Vector3D.h"
#include "Matrix4x4.h"

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


    Matrix4x4 temp;
    Matrix4x4 world_cam;

    world_cam.setIdentity();

    temp.setIdentity();
    temp.setRotationX(m_rot_x);
    world_cam *= temp;

    temp.setIdentity();
    temp.setRotationY(m_rot_y);
    world_cam *= temp;


    Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.1f);

    new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 0.1f);

    world_cam.setTranslation(new_pos);

    m_world_cam = world_cam;


    world_cam.inverse();

    m_world_cam = world_cam;



}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
    Window::onCreate();
    GraphicsEngine::get()->init();
    m_swap_chain = GraphicsEngine::get()->createSwapChain();

    InputSystem::initialize();
    InputSystem::getInstance()->addListener(this);


    RECT rc = this->getClientWindowRect();
    m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);


    Cube* cube = new Cube("1", (this->getClientWindowRect().right - this->getClientWindowRect().left), (this->getClientWindowRect().bottom - this->getClientWindowRect().top));
    cube->setScale(Vector3D(0.2f, 0.2f, 0.2f));
    cube->setPosition(Vector3D(0, 0.3f, 0));
    cube->SetAnimationSpeed(5);

    Cube* cube1 = new Cube("2", (this->getClientWindowRect().right - this->getClientWindowRect().left), (this->getClientWindowRect().bottom - this->getClientWindowRect().top));
    cube1->setScale(Vector3D(0.5f, 0.5f, 0.5f));
    cube1->setPosition(Vector3D(0, -0.45f, 0));
    cube1->SetAnimationSpeed(10);

    Cube* cube2 = new Cube("3", (this->getClientWindowRect().right - this->getClientWindowRect().left), (this->getClientWindowRect().bottom - this->getClientWindowRect().top));
    cube2->setScale(Vector3D(0.35f, 0.35f, 0.35f));
    cube2->setPosition(Vector3D(0, 0, 0));
    cube2->SetAnimationSpeed(3);

    cubeList.push_back(cube);
    cubeList.push_back(cube1);
    cubeList.push_back(cube2);

}

void AppWindow::onUpdate()
{
    InputSystem::getInstance()->update();

    Window::onUpdate();
    //CLEAR THE RENDER TARGET 
    GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
        0, 0.3f, 0.4f, 1);
    //SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
    RECT rc = this->getClientWindowRect();
    GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);


    UpdateCamera();



    for (Cube* cube : cubeList)
    {
        cube->OnUpdate();
        cube->Draw();
    }


  
    m_swap_chain->present(true);

    m_old_delta = m_new_delta;
    m_new_delta = ::GetTickCount();

    m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;
}

void AppWindow::onDestroy()
{
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
    /*
    //cout << "onkeydown:\n";
    if (InputSystem::getInstance()->isKeyDown('W'))
    {
        cout << "W pressed\n";
    }
    */
}

void AppWindow::onKeyUp(int key)
{
    /*
    cout << "onkeyup:\n";
    if (InputSystem::getInstance()->isKeyUp('W'))
    {
        cout << "W released\n";
    }
    */
}

void AppWindow::onMouseMove(const Point deltaPos)
{
    //cout << " mouse moved: " << deltaPos.getX() << ", " << deltaPos.getY() << "\n";
    int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
    int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);



    m_rot_x += (deltaPos.getY() - (height / 2.0f)) * m_delta_time * 0.1f;
    m_rot_y += (deltaPos.getX() - (width / 2.0f)) * m_delta_time * 0.1f;



    //InputSystem::getInstance()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));

}

void AppWindow::onLeftMouseDown(const Point deltaPos)
{
}

void AppWindow::onLeftMouseUp(const Point deltaPos)
{
}

void AppWindow::onRightMouseDown(const Point deltaPos)
{
}

void AppWindow::onRightMouseUp(const Point deltaPos)
{
}
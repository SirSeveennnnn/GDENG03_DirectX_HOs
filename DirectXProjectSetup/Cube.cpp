#include "Cube.h"
#include <iostream>

#include "GraphicsEngine.h"

using namespace std;

__declspec(align(16))
struct constant
{
    Matrix4x4 m_world;
    Matrix4x4 m_view;
    Matrix4x4 m_proj;
    unsigned int m_time;
};

struct vertex
{
    Vector3D position;
    Vector3D color;
    Vector3D color1;
};

Cube::Cube(float screenW, float screenH)
{

    screenWidth = screenW;
    screenHeight = screenH;

    cout << "Cube Init" << endl;
    vertex vertex_list[] =
    {
        //X - Y - Z
        //FRONT FACE
        {Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
        {Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
        { Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
        { Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

        //BACK FACE
        { Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
        { Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
        { Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
        { Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }

    };

    m_vb = GraphicsEngine::get()->createVertexBuffer();
    UINT size_list = ARRAYSIZE(vertex_list);


    unsigned int index_list[] =
    {
        //FRONT SIDE
        0,1,2,  //FIRST TRIANGLE
        2,3,0,  //SECOND TRIANGLE
        //BACK SIDE
        4,5,6,
        6,7,4,
        //TOP SIDE
        1,6,5,
        5,2,1,
        //BOTTOM SIDE
        7,0,3,
        3,4,7,
        //RIGHT SIDE
        3,2,5,
        5,4,3,
        //LEFT SIDE
        7,6,1,
        1,0,7
    };


    m_ib = GraphicsEngine::get()->createIndexBuffer();
    UINT size_index_list = ARRAYSIZE(index_list);

    m_ib->load(index_list, size_index_list);




    void* shader_byte_code = nullptr;
    size_t size_shader = 0;
    GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

    m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
    m_vb->load(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader);

    GraphicsEngine::get()->releaseCompiledShader();


    GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
    m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
    GraphicsEngine::get()->releaseCompiledShader();

    constant cc;
    cc.m_time = 0;

    m_cb = GraphicsEngine::get()->createConstantBuffer();
    m_cb->load(&cc, sizeof(constant));

    SetPosition(Vector3D(0, 0, 0));
    SetScale(Vector3D(0.2f, 0.2f, 0.2f));

    cout << "Gameobject Pos: " << position.m_x << ", " << position.m_y << ", " << position.m_z << endl;
}

Cube::~Cube()
{
}

void Cube::OnUpdate()
{
    rotation.m_y += 0.01f * animationSpeed;

    constant cc;
    cc.m_time = EngineTime::getDeltaTime();
  
    cc.m_world.setScale(scale);
    cc.m_world.setTranslation(position);

    Matrix4x4 temp;
    temp.setIdentity();
    temp.setRotationY(rotation.m_y);
    cc.m_world *= temp;


    cc.m_view.setIdentity();
    cc.m_proj.setOrthoLH
    (
        (screenWidth) / 300.0f,
        (screenHeight) / 300.0f,
        -4.0f,
        4.0f
    );


    m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}

void Cube::Draw()
{
    GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
    GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

    //SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
    GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
    GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);


    //SET THE VERTICES OF THE TRIANGLE TO DRAW
    GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
    //SET THE INDICES OF THE TRIANGLE TO DRAW
    GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);


    // FINALLY DRAW THE TRIANGLE
    GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
   
}

void Cube::SetAnimationSpeed(float speed)
{
    animationSpeed = speed;
}
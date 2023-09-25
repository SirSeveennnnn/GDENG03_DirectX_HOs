#include "AppWindow.h"




AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	/*
	Vertex list[] =
	{
		//X - Y - Z
		{0.80f,0.30f,0.0f},        // INDEX 0
		{0.30f,0.30f,0.0f},        // INDEX 1
		{0.80f,0.80f,0.0f},        // INDEX 2
		{0.30f,0.80f,0.0f},        // INDEX 3

		{0.25f,-0.25f,0.0f},    // INDEX 4
		{-0.25f,-0.25f,0.0f},    // INDEX 5
		{0.25f,0.25f,0.0f},        // INDEX 6
		{-0.25f,0.25f,0.0f},    // INDEX 7

		{-0.30f,-0.80f,0.0f},    // INDEX 8
		{-0.80f,-0.80f,0.0f},    // INDEX 9
		{-0.30f,-0.30f,0.0f},    // INDEX 10
		{-0.80f,-0.30f,0.0f}    // INDEX 11
	};
	*/
	Vertex* vertex1 = new Vertex();
	vertex1->position.x = 0.80f;
	vertex1->position.y = 0.30f;
	vertex1->position.z = 0.0f;

	Vertex* vertex2 = new Vertex();
	vertex2->position.x = 0.30f;
	vertex2->position.y = 0.30f;
	vertex2->position.z = 0.0f;

	Vertex* vertex3 = new Vertex();
	vertex3->position.x = 0.80f;
	vertex3->position.y = 0.80f;
	vertex3->position.z = 0.0f;

	Vertex* vertex4 = new Vertex();
	vertex4->position.x = 0.30f;
	vertex4->position.y = 0.80f;
	vertex4->position.z = 0.0f;
	Quad* quad1 = new Quad(*vertex1, *vertex2, *vertex3, *vertex4);

	

	Vertex* vertex5 = new Vertex(); 
	vertex5->position.x = 0.25f;//{0.25f, -0.25f, 0.0f},    // INDEX 4
	vertex5->position.y = -0.25f;
	vertex5->position.z = 0.0f;

	Vertex* vertex6 = new Vertex();
	vertex6->position.x = -0.25f;//{-0.25f,-0.25f,0.0f},    // INDEX 5
	vertex6->position.y = -0.25f;
	vertex6->position.z = 0.0f;

	Vertex* vertex7 = new Vertex();
	vertex7->position.x = 0.25f;// {0.25f, 0.25f, 0.0f},        // INDEX 6
	vertex7->position.y = 0.25f;
	vertex7->position.z = 0.0f;

	Vertex* vertex8 = new Vertex();
	vertex8->position.x = -0.25f;//{-0.25f,0.25f,0.0f},    // INDEX 7
	vertex8->position.y = 0.25f;
	vertex8->position.z = 0.0f;
	Quad* quad2 = new Quad(*vertex5, *vertex6, *vertex7, *vertex8);

	Vertex* vertex9 = new Vertex();
	vertex5->position.x = -0.30f;//{-0.30f, -0.25f, 0.0f},    // INDEX 4
	vertex5->position.y = -0.80f;
	vertex5->position.z = 0.0f;

	Vertex* vertex10 = new Vertex();
	vertex6->position.x = -0.80;//{-0.25f,-0.25f,0.0f},    // INDEX 5
	vertex6->position.y = -0.80f;
	vertex6->position.z = 0.0f;

	Vertex* vertex11 = new Vertex();
	vertex7->position.x = -0.30f;// {0.25f, 0.25f, 0.0f},        // INDEX 6
	vertex7->position.y = -0.30f;
	vertex7->position.z = 0.0f;

	Vertex* vertex12 = new Vertex();
	vertex8->position.x = -0.80f;//{-0.25f,0.25f,0.0f},    // INDEX 7
	vertex8->position.y = -0.30f;
	vertex8->position.z = 0.0f;
	Quad* quad3 = new Quad(*vertex5, *vertex6, *vertex7, *vertex8);

	QuadList.push_back(quad1);
	QuadList.push_back(quad2);
	QuadList.push_back(quad3);

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0.0f, 0.7f, 0.7f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->setShaders();

	for (Quad* quad : QuadList)
	{
		quad->DrawQuad();
	}

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->release();
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}
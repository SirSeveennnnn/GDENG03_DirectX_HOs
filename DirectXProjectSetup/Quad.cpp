#include "Quad.h"

Quad::Quad(Vertex a, Vertex b, Vertex c, Vertex d)
{
	vertexList[0] = a;
	vertexList[1] = b;
	vertexList[2] = c;
	vertexList[3] = d;

	CreateQuad();
}

Quad::~Quad()
{
}

void Quad::CreateQuad()
{
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertexList);

	GraphicsEngine::get()->createShaders();

	void* shader_byte_code = nullptr;
	UINT size_shader = 0;
	GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	m_vb->load(&vertexList[0], sizeof(Vertex), size_list, shader_byte_code, size_shader);
	
}

void Quad::DrawQuad()
{
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);
}

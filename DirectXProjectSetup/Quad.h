#pragma once
#include "Vertex.h"
#include "VertexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

class Quad
{
public:
	Quad(Vertex a, Vertex b, Vertex c, Vertex d);
	~Quad();
	void DrawQuad();
	

	Vertex vertexList[4];
	VertexBuffer* m_vb;

private:
	

	void CreateQuad();
};


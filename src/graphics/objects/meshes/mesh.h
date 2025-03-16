#pragma once

#include <vector>
#include <memory>

#include "../bindable/buffers/vertexBuffer.h"
#include "../bindable/buffers/indexBuffer.h"

class Mesh {
public:
	struct Vertex {
		dx::XMFLOAT3 pos;
		dx::XMFLOAT3 normal;
		dx::XMFLOAT2 tex;
	};

	std::shared_ptr<VertexBuffer> vertexBuffer;
	std::shared_ptr<IndexBuffer> indexBuffer;
protected:
	std::vector<Vertex> vertices;
	std::vector<unsigned short> indices;
	void calculateNormals();

};
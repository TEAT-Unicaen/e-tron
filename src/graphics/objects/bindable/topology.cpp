#include "topology.h"

Topology::Topology(Renderer& renderer, D3D11_PRIMITIVE_TOPOLOGY type)
	: type(type) {}

void Topology::bind(Renderer& renderer) {
	HR_PLUS;
	CHECK_INFO_ONLY_EXCEPT(this->getDeviceContext(renderer)->IASetPrimitiveTopology(this->type));
}
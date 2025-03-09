#include "mesh.h"

void Mesh::calculateNormals() {
	for (size_t i = 0; i < this->indices.size(); i += 3) {
		auto idx0 = this->indices[i];
		auto idx1 = this->indices[i + 1];
		auto idx2 = this->indices[i + 2];
		auto& v0 = this->vertices[idx0];
		auto& v1 = this->vertices[idx1];
		auto& v2 = this->vertices[idx2];
		dx::XMFLOAT3 edge1 = {
			v1.pos.x - v0.pos.x,
			v1.pos.y - v0.pos.y,
			v1.pos.z - v0.pos.z
		};
		dx::XMFLOAT3 edge2 = {
			v2.pos.x - v0.pos.x,
			v2.pos.y - v0.pos.y,
			v2.pos.z - v0.pos.z
		};
		dx::XMFLOAT3 normal = {
			edge1.y * edge2.z - edge1.z * edge2.y,
			edge1.z * edge2.x - edge1.x * edge2.z,
			edge1.x * edge2.y - edge1.y * edge2.x
		};
		dx::XMVECTOR normalVec = dx::XMVector3Normalize(dx::XMLoadFloat3(&normal));
		dx::XMStoreFloat3(&normal, normalVec);
		v0.normal.x += normal.x;
		v0.normal.y += normal.y;
		v0.normal.z += normal.z;
		v1.normal.x += normal.x;
		v1.normal.y += normal.y;
		v1.normal.z += normal.z;
		v2.normal.x += normal.x;
		v2.normal.y += normal.y;
		v2.normal.z += normal.z;
	}
	for (auto& v : this->vertices) {
		dx::XMVECTOR normalVec = dx::XMVector3Normalize(dx::XMLoadFloat3(&v.normal));
		dx::XMStoreFloat3(&v.normal, normalVec);
	}
}
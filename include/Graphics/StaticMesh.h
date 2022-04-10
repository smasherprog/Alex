#pragma once
#include "Alex.h"
#include "Graphics/Vertex.h"

namespace Alex {
	struct StaticMesh { 
		StaticMesh(const VertexLayout& vertexlayout) : VertexCount(0), IndexCount(0), VertexLayout(vertexlayout) {}
		StaticMesh(const std::vector<Component>& components) : VertexCount(0), IndexCount(0), VertexLayout(components) {}
		std::string MeshPath;
		std::vector<float> VertexBuffer;
		VertexLayout VertexLayout;
		uint32_t VertexCount;
		std::vector<uint32_t> IndexBuffer;
		uint32_t IndexCount;
		struct Dimension
		{
			glm::vec3 min = glm::vec3(FLT_MAX);
			glm::vec3 max = glm::vec3(-FLT_MAX);
			glm::vec3 size = glm::vec3(0);
		} Extent;
	};
}
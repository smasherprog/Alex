#pragma once
#include "Alex.h"
#include "Graphics/StaticMesh.h"
#include "Graphics/Vertex.h"

namespace Alex {

	class StaticMeshFactory {
		std::map<std::string, std::shared_ptr<StaticMesh>> StaticMeshCache;	
		std::shared_ptr<StaticMesh> LoadFromCache(const std::string& path, const VertexLayout& vertexlayout);
		std::shared_ptr<StaticMesh> LoadToCache(const std::string& path, const VertexLayout& vertexlayout);

	public:
		std::shared_ptr<StaticMesh> Load(std::string path, const VertexLayout& vertexlayout);
	};
}
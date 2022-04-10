#include "Graphics/StaticMeshFactory.h"

namespace Alex {
	std::shared_ptr<StaticMesh> StaticMeshFactory::LoadFromCache(const std::string& path, const VertexLayout& vertexlayout) {
		auto f = StaticMeshCache.find(path);
		if (f != StaticMeshCache.end() && f->second->VertexLayout == vertexlayout) {
			return f->second;
		}

		return nullptr;
	}

	std::shared_ptr<StaticMesh> StaticMeshFactory::LoadToCache(const std::string& path, const VertexLayout& vertexlayout) {
		Assimp::Importer importer;
		auto pScene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_Quality);
		if (!pScene) {
			return nullptr;
		}

		auto ptr = std::make_shared<StaticMesh>(vertexlayout);
		ptr->MeshPath = path;
		ptr->VertexLayout = vertexlayout;
		for (unsigned int i = 0; i < pScene->mNumMeshes; i++)
		{
			const aiMesh* paiMesh = pScene->mMeshes[i];
			aiColor3D pColor(0.f, 0.f, 0.f);
			pScene->mMaterials[paiMesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_DIFFUSE, pColor);
			const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
			for (unsigned int j = 0; j < paiMesh->mNumVertices; j++)
			{
				const aiVector3D* pPos = &(paiMesh->mVertices[j]);
				const aiVector3D* pNormal = &(paiMesh->mNormals[j]);
				const aiVector3D* pTexCoord = (paiMesh->HasTextureCoords(0)) ? &(paiMesh->mTextureCoords[0][j]) : &Zero3D;
				const aiVector3D* pTangent = (paiMesh->HasTangentsAndBitangents()) ? &(paiMesh->mTangents[j]) : &Zero3D;
				const aiVector3D* pBiTangent = (paiMesh->HasTangentsAndBitangents()) ? &(paiMesh->mBitangents[j]) : &Zero3D;

				for (auto component : vertexlayout.Components())
				{
					switch (component) {
					case Component::VERTEX_COMPONENT_POSITION:
						ptr->VertexBuffer.push_back(pPos->x);
						ptr->VertexBuffer.push_back(pPos->y);
						ptr->VertexBuffer.push_back(pPos->z);
						break;
					case Component::VERTEX_COMPONENT_NORMAL:
						ptr->VertexBuffer.push_back(pNormal->x);
						ptr->VertexBuffer.push_back(pNormal->y);
						ptr->VertexBuffer.push_back(pNormal->z);
						break;
					case Component::VERTEX_COMPONENT_UV:
						ptr->VertexBuffer.push_back(pTexCoord->x);
						ptr->VertexBuffer.push_back(pTexCoord->y);
						break;
					case Component::VERTEX_COMPONENT_COLOR:
						ptr->VertexBuffer.push_back(pColor.r);
						ptr->VertexBuffer.push_back(pColor.g);
						ptr->VertexBuffer.push_back(pColor.b);
						break;
					case Component::VERTEX_COMPONENT_TANGENT:
						ptr->VertexBuffer.push_back(pTangent->x);
						ptr->VertexBuffer.push_back(pTangent->y);
						ptr->VertexBuffer.push_back(pTangent->z);
						break;
					case Component::VERTEX_COMPONENT_BITANGENT:
						ptr->VertexBuffer.push_back(pBiTangent->x);
						ptr->VertexBuffer.push_back(pBiTangent->y);
						ptr->VertexBuffer.push_back(pBiTangent->z);
						break;
						// Dummy components for padding
					case Component::VERTEX_COMPONENT_DUMMY_FLOAT:
						ptr->VertexBuffer.push_back(0.0f);
						break;
					case Component::VERTEX_COMPONENT_DUMMY_VEC4:
						ptr->VertexBuffer.push_back(0.0f);
						ptr->VertexBuffer.push_back(0.0f);
						ptr->VertexBuffer.push_back(0.0f);
						ptr->VertexBuffer.push_back(0.0f);
						break;
					};
				}

				ptr->Extent.max.x = fmax(pPos->x, ptr->Extent.max.x);
				ptr->Extent.max.y = fmax(pPos->y, ptr->Extent.max.y);
				ptr->Extent.max.z = fmax(pPos->z, ptr->Extent.max.z);

				ptr->Extent.min.x = fmin(pPos->x, ptr->Extent.min.x);
				ptr->Extent.min.y = fmin(pPos->y, ptr->Extent.min.y);
				ptr->Extent.min.z = fmin(pPos->z, ptr->Extent.min.z);
			}

			ptr->Extent.size = ptr->Extent.max - ptr->Extent.min;
			ptr->VertexCount += pScene->mMeshes[i]->mNumVertices;
			auto indexBase = static_cast<uint32_t>(ptr->IndexBuffer.size());
			for (unsigned int j = 0; j < paiMesh->mNumFaces; j++)
			{
				auto& face = paiMesh->mFaces[j];
				if (face.mNumIndices != 3) {
					continue;
				}

				ptr->IndexBuffer.push_back(indexBase + face.mIndices[0]);
				ptr->IndexBuffer.push_back(indexBase + face.mIndices[1]);
				ptr->IndexBuffer.push_back(indexBase + face.mIndices[2]);
			}
		}

		StaticMeshCache.insert({ path, ptr });
		return ptr;
	}

	std::shared_ptr<StaticMesh> StaticMeshFactory::Load(std::string path, const VertexLayout& vertexlayout) {
		std::transform(path.begin(), path.end(), path.begin(), std::tolower);
		auto cached = LoadFromCache(path, vertexlayout);
		if (cached) {
			return cached;
		}

		return LoadToCache(path, vertexlayout);
	}
}

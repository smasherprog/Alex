#pragma once
#include "Alex.h"

namespace Alex {
	 enum class Component {
		VERTEX_COMPONENT_POSITION,
		VERTEX_COMPONENT_NORMAL,
		VERTEX_COMPONENT_COLOR, 
		VERTEX_COMPONENT_UV,
		VERTEX_COMPONENT_TANGENT,
		VERTEX_COMPONENT_BITANGENT,
		VERTEX_COMPONENT_DUMMY_FLOAT,
		VERTEX_COMPONENT_DUMMY_VEC4
	};

	class VertexLayout {
	public:
		VertexLayout(const VertexLayout& vl) = default;
		VertexLayout(const std::vector<Component>& components) : VectorComponets(components)
		{
			for (auto& component : VectorComponets)
			{
				switch (component)
				{
				case Component::VERTEX_COMPONENT_UV:
					VectorStride += 2 * sizeof(float);
					break;
				case Component::VERTEX_COMPONENT_DUMMY_FLOAT:
					VectorStride += sizeof(float);
					break;
				case Component::VERTEX_COMPONENT_DUMMY_VEC4:
					VectorStride += 4 * sizeof(float);
					break;
				default:
					// All components except the ones listed above are made up of 3 floats
					VectorStride += 3 * sizeof(float);
				}
			}
		}

		uint32_t stride() const
		{
			return VectorStride;
		}

		const std::vector<Component>& Components() const
		{
			return VectorComponets;
		}

		friend bool operator== (const VertexLayout& o1, const VertexLayout& o2);
		friend bool operator!= (const VertexLayout& o1, const VertexLayout& o2);
	private:
		std::vector<Component> VectorComponets;
		uint32_t VectorStride = 0;
	};
}
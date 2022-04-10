#include "Graphics/Vertex.h"

namespace Alex {
	bool operator== (const VertexLayout& o1, const VertexLayout& o2)
	{
		if (o1.VectorComponets.size() != o2.VectorComponets.size()) {
			return false;
		}

		for (auto i = 0; i < o1.VectorComponets.size(); i++) {
			if (o1.VectorComponets[i] != o2.VectorComponets[i]) {
				return false;
			}
		}

		return true;
	}

	bool operator!= (const VertexLayout& o1, const VertexLayout& o2)
	{
		return !(o1 == o2);
	}
}


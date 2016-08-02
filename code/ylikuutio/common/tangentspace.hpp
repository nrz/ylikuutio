// Include standard headers
#include <vector>    // std::vector

#ifndef TANGENTSPACE_HPP
#define TANGENTSPACE_HPP

void computeTangentBasis(
	// inputs
	std::vector<glm::vec3>& vertices,
	std::vector<glm::vec2>& UVs,
	std::vector<glm::vec3>& normals,
	// outputs
	std::vector<glm::vec3>& tangents,
	std::vector<glm::vec3>& bitangents
);

#endif

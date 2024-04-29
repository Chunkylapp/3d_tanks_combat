#pragma once

#include <vector>

#include "core/engine.h"
#include "core/gpu/mesh.h"
#include "utils/gl_utils.h"

namespace T1_MeshFactory {

	Mesh* CreateRectangle(const std::string& name, glm::vec3 color,glm::vec2 sizes, bool fill = true);

	Mesh* CreateTurret(const std::string& name, glm::vec3 color, glm::vec2 sizes, bool fill = true);

	Mesh* CreateStar(const std::string& name, glm::vec3 color, glm::vec2 sizes, bool fill = true);

	Mesh* CreateHexagone(const std::string& name, glm::vec3 color, glm::vec2 sizes, bool fill = true);
}
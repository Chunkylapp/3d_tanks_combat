#include "T1_MeshFactory.h"

Mesh* T1_MeshFactory::CreateRectangle(const std::string& name, glm::vec3 color, glm::vec2 sizes, bool fill) {
	
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-1 * sizes.x / 2, -1 * sizes.y / 2, -2), color),
        VertexFormat(glm::vec3(- 1 * sizes.x / 2, 1 * sizes.y / 2, -2), color),
        VertexFormat(glm::vec3(1 * sizes.x / 2, 1 * sizes.y / 2, -2), color),
        VertexFormat(glm::vec3(1 * sizes.x / 2, -1 * sizes.y / 2, -2), color)
        
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices =
    { 
        0, 1, 2,
        3, // 0 and 2 to be added if fill
    };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* T1_MeshFactory::CreateTurret(const std::string& name, glm::vec3 color, glm::vec2 sizes, bool fill) {
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3( 0.f,  6.f, -1.f), color), // 0 A
        VertexFormat(glm::vec3( 3.f,  0.f, -1.f), color), // 1 C
        VertexFormat(glm::vec3( 0.f, -6.f, -1.f), color), // 2 B
        VertexFormat(glm::vec3(-3.f,  0.f, -1.f), color), // 3 D
        VertexFormat(glm::vec3( 2.f,  1.f, -1.f), color), // 4 E
        VertexFormat(glm::vec3( 2.f, -1.f, -1.f), color), // 5 F
        VertexFormat(glm::vec3( 5.f, -1.f, -1.f), color), // 6 G
        VertexFormat(glm::vec3( 5.f,  1.f, -1.f), color), // 7 H
        VertexFormat(glm::vec3( 6.f,  2.f, -1.f), color), // 8 J
        VertexFormat(glm::vec3( 5.f,  0.f, -1.f), color), // 9 K
        VertexFormat(glm::vec3( 6.f, -2.f, -1.f), color), //10 R

        // eyes
        VertexFormat(glm::vec3(0.5f,  3.5f, 0.f), glm::vec3(0.0f)),
        VertexFormat(glm::vec3(0.5f, 1.f, 0.f), glm::vec3(0.0f)),
        VertexFormat(glm::vec3(2.f,  1.f, 0.f), glm::vec3(0.0f))

    };

	Mesh* turret = new Mesh(name);
	std::vector<unsigned int> indices =
    { 
        // rhomb
        0, 1, 2,
        3, 0, 2,
        // rectangle
        4, 7, 6,
		6, 5, 4,
        // end triangles
		7, 8, 9,
		9, 10, 6,

        11, 12, 13
    };

    turret->InitFromData(vertices, indices);
	return turret;
}

Mesh* T1_MeshFactory::CreateStar(const std::string& name, glm::vec3 color, glm::vec2 sizes, bool fill)
{
	std::vector<VertexFormat> vertices =
	{
        // top triangle
		VertexFormat(glm::vec3( 0.f,  5.f, 5.f), color), // 0
		VertexFormat(glm::vec3(-1.1225f, 1.545f, 5.f), color), // 1
		VertexFormat(glm::vec3(1.1225f, 1.545f, 5.f), color), // 2
        // middle triangle
		VertexFormat(glm::vec3(-4.75528f,  1.545f, 5.f), color), // 3
		VertexFormat(glm::vec3(4.75528f,  1.545f, 5.f), color), // 4
		VertexFormat(glm::vec3( 0.f, -1.90983f, 5.f), color), // 5
        // bottom left triangle
		VertexFormat(glm::vec3(-1.816355, -0.59f, 5.f), color), // 6
		VertexFormat(glm::vec3(-2.9389f,     -4.045f, 5.f), color), // 7
        // bottom right triangle
        VertexFormat(glm::vec3( 1.816355, -0.59f, 5.f), color), // 8
        VertexFormat(glm::vec3(2.9389f,     -4.045f, 5.f), color), // 9

	};

	Mesh* star = new Mesh(name);
	std::vector<unsigned int> indices =
	{
		0, 1, 2,
		3, 4, 5,
        6, 5, 7,
        8, 5, 9
	};

	star->InitFromData(vertices, indices);
	return star;
}

Mesh* T1_MeshFactory::CreateHexagone(const std::string& name, glm::vec3 color, glm::vec2 sizes, bool fill)
{
    glm::vec3 insideCL(0.0f, 1.0f, 1.0f);
	std::vector<VertexFormat> vertices =
	{
		// bottom hex
		VertexFormat(glm::vec3(0.f,  0.f, 1.f), color),// center
        VertexFormat(glm::vec3(5.f * cos(glm::radians(0.f)),  5.f * sin(0.f), 1.f), color), // A
        VertexFormat(glm::vec3(5.f * cos(glm::radians(60.f)),  5.f * sin(glm::radians(60.f)), 1.f), color), // B
        VertexFormat(glm::vec3(5.f * cos(glm::radians(120.f)),  5.f * sin(glm::radians(120.f)), 1.f), color), // C
        VertexFormat(glm::vec3(5.f * cos(glm::radians(180.f)),  5.f * sin(glm::radians(180.f)), 1.f), color), // D
        VertexFormat(glm::vec3(5.f * cos(glm::radians(240.f)),  5.f * sin(glm::radians(240.f)), 1.f), color), // E
        VertexFormat(glm::vec3(5.f * cos(glm::radians(300.f)),  5.f * sin(glm::radians(300.f)), 1.f), color), // F

        // top hex
		VertexFormat(glm::vec3(0.f,  0.f, 2.f), insideCL),// center
		VertexFormat(glm::vec3(3.f * cos(glm::radians(0.f)),  3.f * sin(0.f), 2.f), insideCL), // A
		VertexFormat(glm::vec3(3.f * cos(glm::radians(60.f)),  3.f * sin(glm::radians(60.f)), 2.f), insideCL), // B
		VertexFormat(glm::vec3(3.f * cos(glm::radians(120.f)),  3.f * sin(glm::radians(120.f)), 2.f), insideCL), // C
		VertexFormat(glm::vec3(3.f * cos(glm::radians(180.f)),  3.f * sin(glm::radians(180.f)), 2.f), insideCL), // D
		VertexFormat(glm::vec3(3.f * cos(glm::radians(240.f)),  3.f * sin(glm::radians(240.f)), 2.f), insideCL), // E
		VertexFormat(glm::vec3(3.f * cos(glm::radians(300.f)),  3.f * sin(glm::radians(300.f)), 2.f), insideCL), // F
	};

	Mesh* hexagone = new Mesh(name);
	std::vector<unsigned int> indices =
	{
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 5,
        0, 5, 6,
        0, 6, 1,
        //
        7, 8, 9,
        7, 9, 10,
        7, 10, 11,
        7, 11, 12,
        7, 12, 13,
        7, 13, 8

	};

    hexagone->InitFromData(vertices, indices);
	return hexagone;
}
#include <iostream>

#include "T1_Core.h"
#include "T1_GameScene.h"
#include "T1_Hostile.h"
#include "T1_HostileManager.h"
#include "T1_MeshFactory.h"
#include "T1_Object.h"
#include "T1_PlayerManager.h"
#include "T1_ProjectileManager.h"
#include "T1_Turret.h";
#include "T1_TurretManager.h"

T1_Core::T1_Core()
{
	myObjects = new std::vector<T1_Object*>();
}

T1_Core::~T1_Core()
{

}

void T1_Core::Core()
{
	std::cout << "Testing\n";
}

void T1_Core::Init()
{
	auto camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	logicSpace.x = 0;       // logic x
	logicSpace.y = 0;       // logic y
	logicSpace.width = 192.0;   // logic width
	logicSpace.height = 108.0;  // logic height

	// Create the scene itself
	myObjects->push_back(new T1_Spawner(std::string("UI_BOX_1"), T1_Object::ObjectType::Spawner, glm::vec2(20, 97.5), glm::vec3(1.0f, 1.0f, 1.0f), T1_Turret::TurretType::Orange));
	myObjects->push_back(new T1_Object(T1_Object::GetRandomString(20), T1_Object::ObjectType::StarUI, glm::vec2(20, 87), glm::vec3(1.0f, 1.0f, 1.0f)));

	myObjects->push_back(new T1_Spawner(std::string("UI_BOX_2"), T1_Object::ObjectType::Spawner, glm::vec2(40, 97.5), glm::vec3(1.0f, 1.0f, 1.0f), T1_Turret::TurretType::Blue));
	myObjects->push_back(new T1_Object(T1_Object::GetRandomString(20), T1_Object::ObjectType::StarUI, glm::vec2(37.5, 87), glm::vec3(1.0f, 1.0f, 1.0f)));
	myObjects->push_back(new T1_Object(T1_Object::GetRandomString(20), T1_Object::ObjectType::StarUI, glm::vec2(42.5, 87), glm::vec3(1.0f, 1.0f, 1.0f)));
	
	myObjects->push_back(new T1_Spawner(std::string("UI_BOX_3"), T1_Object::ObjectType::Spawner, glm::vec2(60, 97.5), glm::vec3(1.0f, 1.0f, 1.0f), T1_Turret::TurretType::Yellow));
	myObjects->push_back(new T1_Object(T1_Object::GetRandomString(20), T1_Object::ObjectType::StarUI, glm::vec2(55, 87), glm::vec3(1.0f, 1.0f, 1.0f)));
	myObjects->push_back(new T1_Object(T1_Object::GetRandomString(20), T1_Object::ObjectType::StarUI, glm::vec2(60, 87), glm::vec3(1.0f, 1.0f, 1.0f)));
	myObjects->push_back(new T1_Object(T1_Object::GetRandomString(20), T1_Object::ObjectType::StarUI, glm::vec2(65, 87), glm::vec3(1.0f, 1.0f, 1.0f)));
	
	myObjects->push_back(new T1_Spawner(std::string("UI_BOX_4"), T1_Object::ObjectType::Spawner, glm::vec2(80, 97.5), glm::vec3(1.0f, 1.0f, 1.0f), T1_Turret::TurretType::Purple));
	myObjects->push_back(new T1_Object(T1_Object::GetRandomString(20), T1_Object::ObjectType::StarUI, glm::vec2(72.5, 87), glm::vec3(1.0f, 1.0f, 1.0f)));
	myObjects->push_back(new T1_Object(T1_Object::GetRandomString(20), T1_Object::ObjectType::StarUI, glm::vec2(77.5, 87), glm::vec3(1.0f, 1.0f, 1.0f)));
	myObjects->push_back(new T1_Object(T1_Object::GetRandomString(20), T1_Object::ObjectType::StarUI, glm::vec2(82.5, 87), glm::vec3(1.0f, 1.0f, 1.0f)));
	myObjects->push_back(new T1_Object(T1_Object::GetRandomString(20), T1_Object::ObjectType::StarUI, glm::vec2(87.5, 87), glm::vec3(1.0f, 1.0f, 1.0f)));
	
	// Row of cells NO_1
	myObjects->push_back(new T1_Cell(std::string("Cell 0 0"), T1_Object::ObjectType::Cell, glm::vec2(20, 20), glm::vec3(0, 1.0f, 0.557f)));
	myObjects->push_back(new T1_Cell(std::string("Cell 0 1"), T1_Object::ObjectType::Cell, glm::vec2(40, 20), glm::vec3(0, 1.0f, 0.557f)));
	myObjects->push_back(new T1_Cell(std::string("Cell 0 2"), T1_Object::ObjectType::Cell, glm::vec2(60, 20), glm::vec3(0, 1.0f, 0.557f)));

	// Row of cells NO_2
	myObjects->push_back(new T1_Cell(std::string("Cell 1 0"), T1_Object::ObjectType::Cell, glm::vec2(20, 40), glm::vec3(0.f, 1.0f, 0.557f)));
	myObjects->push_back(new T1_Cell(std::string("Cell 1 1"), T1_Object::ObjectType::Cell, glm::vec2(40, 40), glm::vec3(0.f, 1.0f, 0.557f)));
	myObjects->push_back(new T1_Cell(std::string("Cell 1 2"), T1_Object::ObjectType::Cell, glm::vec2(60, 40), glm::vec3(0.f, 1.0f, 0.557f)));

	// Row of cells NO_3
	myObjects->push_back(new T1_Cell(std::string("Cell 2 0"), T1_Object::ObjectType::Cell, glm::vec2(20, 60), glm::vec3(0.f, 1.0f, 0.557f)));
	myObjects->push_back(new T1_Cell(std::string("Cell 2 1"), T1_Object::ObjectType::Cell, glm::vec2(40, 60), glm::vec3(0.f, 1.0f, 0.557f)));
	myObjects->push_back(new T1_Cell(std::string("Cell 2 2"), T1_Object::ObjectType::Cell, glm::vec2(60, 60), glm::vec3(0.f, 1.0f, 0.557f)));

	// Row of red line
	myObjects->push_back(new T1_RedLine(std::string("Red Line"), T1_Object::ObjectType::RedLine, glm::vec2(2.5, 40), glm::vec3(1.0f, 0.0f, 0.0f)));

	myObjects->push_back(new T1_Object(std::string("UI_Container"), T1_Object::ObjectType::UIContainer, glm::vec2(81, 95), glm::vec3(0.0f, 0.408f, 0.459f)));

	// hp module with 3 squares
	// myObjects->push_back()

	myPlaceable = nullptr;
}

void T1_Core::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(1, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void T1_Core::Update(float myDeltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();
	viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
	SetViewportArea(viewSpace, glm::vec3(0), true);

	glm::mat3 visMatrix = glm::mat3(1);
	visMatrix *= VisualizationTransf2D(logicSpace, viewSpace);

	//player update
	T1_PlayerManager* playerManager = T1_PlayerManager::GetManager();
	playerManager->Update(myDeltaTimeSeconds);

	// if turret update
	T1_TurretManager* turretManager = T1_TurretManager::GetManager();
	turretManager->Update(myDeltaTimeSeconds);

	//projectile update
	T1_ProjectileManager* projectileManager = T1_ProjectileManager::GetManager();
	projectileManager->Update(myDeltaTimeSeconds);

	// hostile update
	T1_HostileManager* hostileManager = T1_HostileManager::GetManager();
	hostileManager->Update(myDeltaTimeSeconds);

	for (int i = 0; i < myObjects->size(); i++)
		(*myObjects)[i]->Update(myDeltaTimeSeconds);

	if (myPlaceable)
		myPlaceable->Draw(this, visMatrix);

	turretManager->Draw(this, visMatrix);
	projectileManager->Draw(this, visMatrix);
	hostileManager->Draw(this, visMatrix);
	playerManager->Draw(this, visMatrix);

	// Render everything on screen
	for (int i = 0; i < myObjects->size(); i++) {
		(*myObjects)[i]->Draw(this, visMatrix);
	}

	if (T1_PlayerManager::GetManager()->GameOver()) {
		exit(0);
	}

}

void T1_Core::OnKeyPress(int key, int mods) {
	switch (key) {
	}

}

void T1_Core::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	glm::mat3 visMatrix = glm::mat3(1);
	visMatrix *= VisualizationTransf2D(logicSpace, viewSpace);
	glm::vec3 mousePoz = glm::inverse(visMatrix) * glm::vec3(mouseX, mouseY, 1);

	for (int i = 0; i < myObjects->size(); i++)
	{
		if (((*myObjects)[i]->GetType() == T1_Spawner::ObjectType::Spawner && ((T1_Spawner*)(*myObjects)[i])->IsDragging())) {
			((T1_Spawner*)(*myObjects)[i])->MoveTurret(mousePoz.x, logicSpace.height - mousePoz.y);
		}
	}
}

void T1_Core::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	switch (button) {
	case GLFW_MOUSE_BUTTON_2:
	{
		glm::mat3 visMatrix = glm::mat3(1);
		visMatrix *= VisualizationTransf2D(logicSpace, viewSpace);
		glm::vec3 mousePoz = glm::inverse(visMatrix) * glm::vec3(mouseX, mouseY, 1);

		for (int i = 0; i < myObjects->size(); i++)
		{
			if (((*myObjects)[i]->GetType() == T1_Spawner::ObjectType::Spawner) && ((T1_Spawner*)(*myObjects)[i])->IsInCell(mousePoz.x, logicSpace.height - mousePoz.y)) {
				// look for the turret that has the same coordinates
				((T1_Spawner*)(*myObjects)[i])->Drag();
				((T1_Spawner*)(*myObjects)[i])->MoveTurret(mousePoz.x, logicSpace.height - mousePoz.y);
			}
		}

		T1_PlayerManager::GetManager()->TryToCollect(mousePoz.x, logicSpace.height - mousePoz.y);
		break;
	}
	case GLFW_MOUSE_BUTTON_3:
	{
		glm::mat3 visMatrix = glm::mat3(1);
		visMatrix *= VisualizationTransf2D(logicSpace, viewSpace);
		glm::vec3 mousePoz = glm::inverse(visMatrix) * glm::vec3(mouseX, mouseY, 1);
		for (int i = 0; i < myObjects->size(); i++)
		{
			if (((*myObjects)[i]->GetType() == T1_Cell::ObjectType::Cell) && ((T1_Cell*)(*myObjects)[i])->IsInCell(mousePoz.x, logicSpace.height - mousePoz.y)) {
				T1_TurretManager* turretManager = T1_TurretManager::GetManager();
				turretManager->Kill(((T1_Cell*)(*myObjects)[i])->GetCenterPosition());
			}
		}
		break;
	}
	}

}

void T1_Core::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {

	switch (button) {
	case GLFW_MOUSE_BUTTON_2:
	{
		glm::mat3 visMatrix = glm::mat3(1);
		visMatrix *= VisualizationTransf2D(logicSpace, viewSpace);
		glm::vec3 mousePoz = glm::inverse(visMatrix) * glm::vec3(mouseX, mouseY, 1);

		T1_Spawner* draggingSpawner = nullptr;

		for (int i = 0; i < myObjects->size(); i++)
			if (((*myObjects)[i]->GetType() == T1_Spawner::ObjectType::Spawner && ((T1_Spawner*)(*myObjects)[i])->IsDragging()))
			{
				draggingSpawner = ((T1_Spawner*)(*myObjects)[i]);
				break;
			}

		if (draggingSpawner) {
			for (int i = 0; i < myObjects->size(); i++)
				if (((*myObjects)[i]->GetType() == T1_Cell::ObjectType::Cell) && ((T1_Cell*)(*myObjects)[i])->IsInCell(mousePoz.x, logicSpace.height - mousePoz.y))
				{
					int turretCost = 0;

					switch (draggingSpawner->GetSpawnerType())
					{
					case T1_Turret::TurretType::Orange:
						turretCost = 1;
						break;
					case T1_Turret::TurretType::Blue:
						turretCost = 2;
						break;
					case T1_Turret::TurretType::Yellow:
						turretCost = 3;
						break;
					case T1_Turret::TurretType::Purple:
						turretCost = 4;
					}

					T1_PlayerManager* playerManager = T1_PlayerManager::GetManager();
					T1_TurretManager* turretManager = T1_TurretManager::GetManager();

					if (playerManager->GetStars() >= turretCost && !turretManager->TurretAtPosition(((T1_Cell*)(*myObjects)[i])->GetCenterPosition())) {

						playerManager->DelStars(turretCost);

						T1_Turret* newTurret = nullptr;

						turretManager->AddTurret(((T1_Cell*)(*myObjects)[i])->GetCenterPosition(), draggingSpawner->GetSpawnerType());
					}
				}
			draggingSpawner->StopDrag();
			break;
		}
	}
	}
}

void T1_Core::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear) {
	glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	glEnable(GL_SCISSOR_TEST);
	glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);

	GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
	GetSceneCamera()->Update();
}

glm::mat3 T1_Core::VisualizationTransf2D(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
{
	float sx, sy, tx, ty;
	sx = viewSpace.width / logicSpace.width;
	sy = viewSpace.height / logicSpace.height;
	tx = viewSpace.x - sx * logicSpace.x;
	ty = viewSpace.y - sy * logicSpace.y;

	return glm::transpose(glm::mat3(
		sx, 0.0f, tx,
		0.0f, sy, ty,
		0.0f, 0.0f, 1.0f));
}
#include <string>

#include "T1_GameScene.h"
#include "T1_MeshFactory.h"
#include "T1_Turret.h"

// ######################################################################################################################################

T1_Cell::T1_Cell(std::string aName, ObjectType aType, glm::vec2 aCenterPosition, glm::vec3 aColor) : T1_Object(aName, aType, aCenterPosition, aColor) {
}

T1_Cell::~T1_Cell() {
}

void T1_Cell::Update(float myDeltaTimeSeconds) {

}

void T1_Cell::Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix)
{
	glm::mat3 modelMatrix = visMatrix * Translate(myCenterPosition.x, myCenterPosition.y);
	aScene->RenderMesh2D(myMesh, aScene->shaders["VertexColor"], modelMatrix);
}

bool T1_Cell::IsInCell(float mouseX, float mouseY) {

	float negX = (-1 * mySizes.x / 2 + myCenterPosition.x);
	float negY = (-1 * mySizes.y / 2 + myCenterPosition.y);

	float posx = (1 * mySizes.y / 2 + myCenterPosition.x);
	float posY = (1 * mySizes.y / 2 + myCenterPosition.y);


	return  (negX < mouseX) &&
		(negY < mouseY) &&
		(posx > mouseX) &&
		(posY > mouseY);
}

// ######################################################################################################################################

T1_RedLine::T1_RedLine(std::string aName, ObjectType aType, glm::vec2 aCenterPosition, glm::vec3 aColor) : T1_Object(aName, aType, aCenterPosition, aColor) {
}

T1_RedLine::~T1_RedLine() {
}

void T1_RedLine::Update(float myDeltaTimeSeconds)
{

}

void T1_RedLine::Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix)
{
	glm::mat3 modelMatrix = visMatrix * Translate(myCenterPosition.x, myCenterPosition.y);
	aScene->RenderMesh2D(myMesh, aScene->shaders["VertexColor"], modelMatrix);
}

// ######################################################################################################################################

T1_Spawner::T1_Spawner(std::string aName, ObjectType aType, glm::vec2 aCenterPosition, glm::vec3 aColor, T1_Turret::TurretType aSpawnType) :
	T1_Object(aName, aType, aCenterPosition, aColor),
	isDragging(false),
	myDragMousePoz(aCenterPosition)
{
	mySpawnerType = aSpawnType;
	myTurret = nullptr;

	switch (mySpawnerType) {
	case T1_Turret::TurretType::Orange:
		myTurret = T1_MeshFactory::CreateTurret(std::string("spawner_turret_orange"), glm::vec3(1.f, 0.5f, 0.0f), aCenterPosition);
		break;
	case T1_Turret::TurretType::Blue:
		myTurret = T1_MeshFactory::CreateTurret(std::string("spawner_turret_blue"), glm::vec3(0.f, 0.0f, 1.f), aCenterPosition);
		break;
	case T1_Turret::TurretType::Yellow:
		myTurret = T1_MeshFactory::CreateTurret(std::string("spawner_turret_yellow"), glm::vec3(1.0f, 1.0f, 0.0f), aCenterPosition);
		break;
	case T1_Turret::TurretType::Purple:
		myTurret = T1_MeshFactory::CreateTurret(std::string("spawner_turret_purple"), glm::vec3(1.0f, 0.0f, 1.0f), aCenterPosition);
		break;
	}
}

T1_Spawner::~T1_Spawner() {
}

void T1_Spawner::Update(float myDeltaTimeSeconds) {

}

void T1_Spawner::Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix)
{
	glm::mat3 modelMatrix = visMatrix * Translate(myCenterPosition.x, myCenterPosition.y);
	aScene->RenderMesh2D(myMesh, aScene->shaders["VertexColor"], modelMatrix);

	modelMatrix = visMatrix * Translate(myDragMousePoz.x, myDragMousePoz.y);
	aScene->RenderMesh2D(myTurret, aScene->shaders["VertexColor"], modelMatrix);
}

bool T1_Spawner::IsInCell(float mouseX, float mouseY) {

	float negX = (-1 * mySizes.x / 2 + myCenterPosition.x);
	float negY = (-1 * mySizes.y / 2 + myCenterPosition.y);

	float posx = (1 * mySizes.y / 2 + myCenterPosition.x);
	float posY = (1 * mySizes.y / 2 + myCenterPosition.y);


	return  (negX < mouseX) &&
		(negY < mouseY) &&
		(posx > mouseX) &&
		(posY > mouseY);
}

void T1_Spawner::MoveTurret(float mouseX, float mouseY) {
	myDragMousePoz.x = mouseX;
	myDragMousePoz.y = mouseY;
}

void T1_Spawner::StopDrag() {
	myDragMousePoz.x = myCenterPosition.x;
	myDragMousePoz.y = myCenterPosition.y;
	isDragging = false;
}

// ######################################################################################################################################

T1_HP::T1_HP(std::string aName, ObjectType aType, glm::vec2 aCenterPosition, glm::vec3 aColor) : T1_Object(aName, aType, aCenterPosition, aColor) {

}

T1_HP::~T1_HP() {
}

void T1_HP::Update(float myDeltaTimeSeconds) {

}

void T1_HP::Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix)
{
	glm::mat3 modelMatrix = visMatrix * Translate(myCenterPosition.x, myCenterPosition.y);
	aScene->RenderMesh2D(myMesh, aScene->shaders["VertexColor"], modelMatrix);
}

// ######################################################################################################################################
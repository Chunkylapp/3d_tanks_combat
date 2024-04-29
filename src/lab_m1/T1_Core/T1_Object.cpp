#include <string>
#include <random>
#include "T1_MeshFactory.h"
#include "T1_Object.h"

T1_Object::T1_Object(std::string aName, ObjectType aType, glm::vec2 aCenterPosition, glm::vec3 aColor) {
	myCenterPosition = aCenterPosition;
	myColor = aColor;
	myType = aType;
	mySizes = glm::vec2(0.0f, 0.0f);

	switch (myType) {
	case ObjectType::Turret:
		mySizes = glm::vec2(10.f, 10.f);
		myMesh = T1_MeshFactory::CreateTurret(aName, aColor, mySizes);
		break;
	case ObjectType::Cell:
		mySizes = glm::vec2(15.f, 15.f);
		myMesh = T1_MeshFactory::CreateRectangle(aName, aColor, mySizes);
		break;
	case ObjectType::RedLine:
		mySizes = glm::vec2(7.5, 55.5f);
		myMesh = T1_MeshFactory::CreateRectangle(aName, aColor, mySizes);
		break;
	case ObjectType::Projectile:
		mySizes = glm::vec2(5.f, 5.f);
		myMesh = T1_MeshFactory::CreateStar(aName, aColor, mySizes);
		break;
	case ObjectType::Spawner:
		mySizes = glm::vec2(15.f, 15.f);
		myMesh = T1_MeshFactory::CreateRectangle(aName, aColor, mySizes, false);
		break;
	case ObjectType::Hostile:
		mySizes = glm::vec2(10.f, 10.f);
		myMesh = T1_MeshFactory::CreateHexagone(aName, aColor, mySizes);
		break;
	case ObjectType::HP:
		mySizes = glm::vec2(15.f, 15.f);
		myMesh = T1_MeshFactory::CreateRectangle(aName, aColor, mySizes);
		break;
	case ObjectType::Collectible:
		mySizes = glm::vec2(10.f, 10.f);
		myMesh = T1_MeshFactory::CreateStar(aName, aColor, mySizes);
		break;
	case ObjectType::StarUI:
		mySizes = glm::vec2(2.5f, 2.5f);
		myMesh = T1_MeshFactory::CreateStar(aName, aColor, mySizes);
		break;
	case ObjectType::UIContainer:
		mySizes = glm::vec2(192.f, 26.f);
		myMesh = T1_MeshFactory::CreateRectangle(aName, aColor, mySizes);
		break;
	default:
		myMesh = nullptr;
	}
	
	myRadius = mySizes.x / 2;
}

T1_Object::~T1_Object() {
	delete myMesh;
}

void T1_Object::Move(float x, float y) {
	myCenterPosition.x = x;
	myCenterPosition.y = y;
}

void T1_Object::Update(float myDeltaTimeSeconds)
{

}

void T1_Object::Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix) {
	glm::mat3 modelMatrix = glm::mat3(1);
	switch (myType)
	{
	case T1_Object::Turret:
		modelMatrix = visMatrix * Translate(myCenterPosition.x, myCenterPosition.y);
		aScene->RenderMesh2D(myMesh, aScene->shaders["VertexColor"], modelMatrix);
		break;
	case T1_Object::Hostile:
		break;
	case T1_Object::Projectile:
		modelMatrix = visMatrix * Translate(myCenterPosition.x, myCenterPosition.y);
		aScene->RenderMesh2D(myMesh, aScene->shaders["VertexColor"], modelMatrix);
		break;
	case T1_Object::StarUI:
		modelMatrix = visMatrix * Translate(myCenterPosition.x, myCenterPosition.y) * Scale(0.5f, 0.5f);
		aScene->RenderMesh2D(myMesh, aScene->shaders["VertexColor"], modelMatrix);
		break;
	default:
		modelMatrix = visMatrix * Translate(myCenterPosition.x, myCenterPosition.y);
		aScene->RenderMesh2D(myMesh, aScene->shaders["VertexColor"], modelMatrix);
		break;
	}



}

std::string T1_Object::GetRandomString(int length) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::string str("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");

	std::shuffle(str.begin(), str.end(), gen);

	return str.substr(0, length);
}

bool T1_Object::IsColliding(T1_Object* anObject, bool checkForColor) {
	if (!checkForColor || anObject->GetColor() == myColor) {
		// (R0 + R1)^2
		float squaredRadiusSum = (myRadius + anObject->GetRadius()) * (myRadius + anObject->GetRadius());
		// (R0 - R1)^2
		float squaredRadiusDifference = (myRadius - anObject->GetRadius()) * (myRadius - anObject->GetRadius());
		// (x0 - x1)^2 since we don't care about the y because they both belong to the same line vector
		float squaredPointDifference = (myCenterPosition.x - anObject->GetCenterPosition().x) * (myCenterPosition.x - anObject->GetCenterPosition().x);

		return (squaredPointDifference <= squaredRadiusSum);
	}
}


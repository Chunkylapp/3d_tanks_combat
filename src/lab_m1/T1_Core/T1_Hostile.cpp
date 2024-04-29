#include "T1_Hostile.h"

T1_Hostile::T1_Hostile(std::string aName, ObjectType aType, glm::vec2 aCenterPosition, glm::vec3 aColor, HostileType aHostileType) :
	T1_Object(aName, aType, aCenterPosition, aColor)
{
	myHP = (aHostileType + 1) * 10;
	myRotation = 0.0f;
	myScale = 1.f;
	isDying = false;
}

T1_Hostile::~T1_Hostile() {

}

void T1_Hostile::Update(float myDeltaTimeSeconds) {
	if (isDying) {
		myScale -= myDeltaTimeSeconds;
		if (myScale <= 0.f) {
			isDying = false;
			myScale = 0;
		}
	}
	else {
		myCenterPosition.x -= 10.f * myDeltaTimeSeconds;
		myRotation -= myDeltaTimeSeconds * 2.5f;
	}
}

void T1_Hostile::Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix) {
	//glm::mat3 modelMatrix = visMatrix * Translate(myCenterPosition.x, myCenterPosition.y) * Rotate(myRotation) * Scale(myScale > 1.f ? 1.f : myScale, myScale > 1.f ? 1.f : myScale);
	glm::mat3 modelMatrix = visMatrix * Translate(myCenterPosition.x, myCenterPosition.y) * Rotate(myRotation) * Scale (myScale, myScale);
	aScene->RenderMesh2D(myMesh, aScene->shaders["VertexColor"], modelMatrix);
}

void T1_Hostile::SetDying() {
	isDying = true;
}
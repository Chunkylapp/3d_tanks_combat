#include "T1_Collectible.h"


T1_Collectible::T1_Collectible(std::string aName, glm::vec2 aCenterPosition, glm::vec3 aColor) :
	T1_Object(aName, ObjectType::Collectible, aCenterPosition, aColor)
{
	myLifeTimeSeconds = 30.f;
	myScale = 1.f;
	isDying = false;
	myAnimationY = myCenterPosition.y;
	myCenterPosition.y = 80.f;
}

T1_Collectible::~T1_Collectible()
{

}

void T1_Collectible::Update(float myDeltaTimeSeconds)
{
	if (isDying) {
		myScale -= myDeltaTimeSeconds;
		if (myScale <= 0.f) {
			isDying = false;
			myScale = 0;
		}
	}
	else {
		myLifeTimeSeconds -= myDeltaTimeSeconds;
		if (myLifeTimeSeconds < 0.f) {
			isDying = true;
		}
	}
	if (myAnimationY <= myCenterPosition.y)
		myCenterPosition.y -= 10 * myDeltaTimeSeconds;
}

void T1_Collectible::Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix)
{
	glm::mat3 modelMatrix = visMatrix * Translate(myCenterPosition.x, myCenterPosition.y) * Scale(myScale, myScale);
	aScene->RenderMesh2D(myMesh, aScene->shaders["VertexColor"], modelMatrix);
}

void T1_Collectible::SetDying() {
	isDying = true;
}
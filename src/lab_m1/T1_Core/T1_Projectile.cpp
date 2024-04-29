#include "T1_Projectile.h"

T1_Projectile::T1_Projectile(std::string aName, ObjectType aType, glm::vec2 aCenterPosition, glm::vec3 aColor, float aDamage) :
	T1_Object(aName, aType, aCenterPosition, aColor),
	myDamage(aDamage)
{
	myRotation = 0.0f;
	myScale = 0.f;
	isDying = false;
}

T1_Projectile::~T1_Projectile() {

}

void T1_Projectile::Update(float myDeltaTimeSeconds)
{
	if (isDying) {
		myScale -= myDeltaTimeSeconds;
		if (myScale <= 0.f) {
			isDying = false;
			myScale = 0;
		}
	}
	else {
		myCenterPosition.x += myDeltaTimeSeconds * 20.f;
		myRotation += myDeltaTimeSeconds * 5.f;
		if (myScale < 1.f)
			myScale += myDeltaTimeSeconds;
		else
			myScale = 1.f;
	}
}

void T1_Projectile::Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix) {
	glm::mat3 modelMatrix = visMatrix * Translate(myCenterPosition.x, myCenterPosition.y) * Rotate(myRotation) * Scale(myScale > 1.f ? 1.f : myScale, myScale > 1.f ? 1.f : myScale);
	aScene->RenderMesh2D(myMesh, aScene->shaders["VertexColor"], modelMatrix);
}

void T1_Projectile::SetDying() {
	isDying = true;
}
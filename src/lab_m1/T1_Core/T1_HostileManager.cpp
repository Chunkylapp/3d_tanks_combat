#include "T1_HostileManager.h"
#include "T1_PlayerManager.h"

T1_HostileManager::T1_HostileManager()
{
	timeToTrySpawn = 60.f;
}

T1_HostileManager::~T1_HostileManager() {

}

T1_HostileManager* T1_HostileManager::theManager = nullptr;

T1_HostileManager* T1_HostileManager::GetManager() {
	if (T1_HostileManager::theManager == nullptr) {
		T1_HostileManager::theManager = new T1_HostileManager();
	}
	return T1_HostileManager::theManager;
}

void T1_HostileManager::Update(float myDeltaTimeSeconds)
{
	timeToTrySpawn -= myDeltaTimeSeconds * 10.f;
	int rand_no = rand() * myDeltaTimeSeconds;
	if (timeToTrySpawn < 0.f && rand_no >=100 &&  rand_no % 10 != 7) {
		timeToTrySpawn = 60.f;

		glm::vec3 color(0.0f, 0.0f, 0.0f);
		T1_Hostile::HostileType hostileType = T1_Hostile::Orange;
		switch (rand_no / 10 % 4) {
		case 0:
			hostileType = T1_Hostile::Orange;
			color = glm::vec3(1.f, 0.5f, 0.0f);
			break;
		case 1:
			hostileType = T1_Hostile::Blue;
			color = glm::vec3(0.f, 0.0f, 1.f);
			break;
		case 2:
			hostileType = T1_Hostile::Yellow;
			color = glm::vec3(1.0f, 1.0f, 0.0f);
			break;
		case 3:
			hostileType = T1_Hostile::Purple;
			color = glm::vec3(1.0f, 0.0f, 1.0f);
			break;
		}
		if (rand_no % 100 > 0 && rand_no % 100 < 40) {
			myHostilesBottom.push_back(new T1_Hostile(T1_Object::GetRandomString(20), T1_Object::Hostile, glm::vec2(200, 20), color, hostileType));
		}
		else {
			if (rand_no % 100 >= 40 && rand_no % 100 <= 70)
				myHostilesMiddle.push_back(new T1_Hostile(T1_Object::GetRandomString(20), T1_Object::Hostile, glm::vec2(200, 40), color, hostileType));
			else
				myHostilesTop.push_back(new T1_Hostile(T1_Object::GetRandomString(20), T1_Object::Hostile, glm::vec2(200, 60), color, hostileType));
		}
	}

	// bottom
	for (int i = 0; i < myHostilesBottom.size(); i++) {
		myHostilesBottom[i]->Update(myDeltaTimeSeconds);

		if (myHostilesBottom[i]->GetCenterPosition().x < 0.f || myHostilesBottom[i]->IsDead()) {
			if (myHostilesBottom[i]->GetCenterPosition().x < 0.f)
				T1_PlayerManager::GetManager()->LoseLifePoint();

			T1_Hostile* ToDelete = myHostilesBottom[i];

			myHostilesBottom.erase(myHostilesBottom.begin() + i, myHostilesBottom.begin() + i + 1);
			delete ToDelete;
			i--;

		}
	}
	// middle
	for (int i = 0; i < myHostilesMiddle.size(); i++) {
		myHostilesMiddle[i]->Update(myDeltaTimeSeconds);

		if (myHostilesMiddle[i]->GetCenterPosition().x < 0.f || myHostilesMiddle[i]->IsDead()) {
			if (myHostilesMiddle[i]->GetCenterPosition().x < 0.f)
				T1_PlayerManager::GetManager()->LoseLifePoint();

			T1_Hostile* ToDelete = myHostilesMiddle[i];

			myHostilesMiddle.erase(myHostilesMiddle.begin() + i, myHostilesMiddle.begin() + i + 1);
			delete ToDelete;
			i--;

		}
	}
	// top
	for (int i = 0; i < myHostilesTop.size(); i++) {
		myHostilesTop[i]->Update(myDeltaTimeSeconds);

		if (myHostilesTop[i]->GetCenterPosition().x < 0.f || myHostilesTop[i]->IsDead()) {
			if (myHostilesTop[i]->GetCenterPosition().x < 0.f)
				T1_PlayerManager::GetManager()->LoseLifePoint();

			T1_Hostile* ToDelete = myHostilesTop[i];

			myHostilesTop.erase(myHostilesTop.begin() + i, myHostilesTop.begin() + i + 1);
			delete ToDelete;
			i--;
		}
	}

}

void T1_HostileManager::Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix)
{
	for (int i = 0; i < myHostilesBottom.size(); i++)
		myHostilesBottom[i]->Draw(aScene, visMatrix);

	for (int i = 0; i < myHostilesMiddle.size(); i++)
		myHostilesMiddle[i]->Draw(aScene, visMatrix);

	for (int i = 0; i < myHostilesTop.size(); i++)
		myHostilesTop[i]->Draw(aScene, visMatrix);
}

bool T1_HostileManager::CollisionCheck(T1_Object* anObject, unsigned short grid, bool checkForColor) {
	switch (grid) {
	case 0:
		for (int i = 0; i < myHostilesBottom.size(); i++)
			if (myHostilesBottom[i]->IsColliding(anObject, checkForColor)) {
				if (anObject->GetType() == T1_Object::ObjectType::Projectile)
					myHostilesBottom[i]->SetDying();
				return true;
			}
		break;
	case 1:
		for (int i = 0; i < myHostilesMiddle.size(); i++)
			if (myHostilesMiddle[i]->IsColliding(anObject, checkForColor)) {
				if (anObject->GetType() == T1_Object::ObjectType::Projectile)
					myHostilesMiddle[i]->SetDying();
				return true;
			}
		break;
	case 2:
		for (int i = 0; i < myHostilesTop.size(); i++)
			if (myHostilesTop[i]->IsColliding(anObject, checkForColor)) {
				if(anObject->GetType() == T1_Object::ObjectType::Projectile)
					myHostilesTop[i]->SetDying();
				return true;
			}
		break;
	}
	return false;
}

bool T1_HostileManager::EnemyTypeOnLine(float  aLineCoordinate, glm::vec3 aColor) {
	int grid = aLineCoordinate;
	switch(grid) {
	case 20:
		for (int i = 0; i < myHostilesBottom.size(); i++)
			if (myHostilesBottom[i]->GetColor() == aColor)
				return true;
		break;
	case 40:
		for (int i = 0; i < myHostilesMiddle.size(); i++)
			if (myHostilesMiddle[i]->GetColor() == aColor)
				return true;
		break;
	case 60:
		for (int i = 0; i < myHostilesTop.size(); i++)
			if (myHostilesTop[i]->GetColor() == aColor)
				return true;
		break;
	}
	return false;
}
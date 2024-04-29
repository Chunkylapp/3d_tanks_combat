

#include "T1_HostileManager.h"
#include "T1_TurretManager.h"

T1_TurretManager::T1_TurretManager() {

}

T1_TurretManager::~T1_TurretManager() {

}

T1_TurretManager* T1_TurretManager::theManager = nullptr;

T1_TurretManager* T1_TurretManager::GetManager() {
	if (T1_TurretManager::theManager == nullptr) {
		T1_TurretManager::theManager = new T1_TurretManager();
	}
	return T1_TurretManager::theManager;
}

void T1_TurretManager::Update(float myDeltaTimeSeconds) {
	T1_HostileManager* hostileManager = T1_HostileManager::GetManager();
	// bottom
	for (int i = 0; i < myTurretsBottom.size(); i++) {
		myTurretsBottom[i]->Update(myDeltaTimeSeconds);
		if (myTurretsBottom[i]->IsDead()) {
			T1_Turret* toDelete = myTurretsBottom[i];
			myTurretsBottom.erase(myTurretsBottom.begin() + i);
			i--;
			delete toDelete;
		}
		else {
			if (hostileManager->CollisionCheck(myTurretsBottom[i], 0, false)) {
				myTurretsBottom[i]->SetDying();
			}
		}
	}
	// middle
	for (int i = 0; i < myTurretsMiddle.size(); i++) {
		myTurretsMiddle[i]->Update(myDeltaTimeSeconds);
		if (myTurretsMiddle[i]->IsDead()) {
			T1_Turret* toDelete = myTurretsMiddle[i];
			myTurretsMiddle.erase(myTurretsMiddle.begin() + i);
			i--;
			delete toDelete;
		}
		else {
			if (hostileManager->CollisionCheck(myTurretsMiddle[i], 1, false)) {
				myTurretsMiddle[i]->SetDying();
			}
		}
	}
	// top
	for (int i = 0; i < myTurretsTop.size(); i++) {
		myTurretsTop[i]->Update(myDeltaTimeSeconds);
		if (myTurretsTop[i]->IsDead()) {
			T1_Turret* toDelete = myTurretsTop[i];
			myTurretsTop.erase(myTurretsTop.begin() + i);
			i--;
			delete toDelete;
		}
		else {
			if (hostileManager->CollisionCheck(myTurretsTop[i], 2, false)) {
				myTurretsTop[i]->SetDying();
			}
		}
	}
}

void T1_TurretManager::Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix) {
	for (int i = 0; i < myTurretsBottom.size(); i++) {
		myTurretsBottom[i]->Draw(aScene, visMatrix);
	}
	for (int i = 0; i < myTurretsMiddle.size(); i++) {
		myTurretsMiddle[i]->Draw(aScene, visMatrix);
	}
	for (int i = 0; i < myTurretsTop.size(); i++) {
		myTurretsTop[i]->Draw(aScene, visMatrix);
	}
}

void T1_TurretManager::AddTurret(glm::vec2 aCenterPosition, T1_Turret::TurretType aType) {
	glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f);
	float hp = 0;
	float damage = 0;


	switch (aType) {
	case T1_Turret::TurretType::Orange:
		color = glm::vec3(1.f, 0.5f, 0.0f);
		hp = 10;
		damage = 5;
		break;
	case T1_Turret::TurretType::Blue:
		color = glm::vec3(0.f, 0.0f, 1.f);
		hp = 20;
		damage = 10;
		break;
	case T1_Turret::TurretType::Yellow:
		color = glm::vec3(1.0f, 1.0f, 0.0f);
		hp = 30;
		damage = 15;
		break;
	case T1_Turret::TurretType::Purple:
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		hp = 40;
		damage = 15;
		break;
	}

	if (aCenterPosition.y == 20.f)
		myTurretsBottom.push_back(new T1_Turret(T1_Object::GetRandomString(20), T1_Object::Turret, aCenterPosition, color, hp, damage));
	else
		if (aCenterPosition.y == 40.f)
			myTurretsMiddle.push_back(new T1_Turret(T1_Object::GetRandomString(20), T1_Object::Turret, aCenterPosition, color, hp, damage));
		else
			myTurretsTop.push_back(new T1_Turret(T1_Object::GetRandomString(20), T1_Object::Turret, aCenterPosition, color, hp, damage));

}

void T1_TurretManager::Kill(glm::vec2 aCenterPosition) {
	for (int i = 0; i < myTurretsBottom.size(); i++)
		if (myTurretsBottom[i]->GetCenterPosition().x == aCenterPosition.x && myTurretsBottom[i]->GetCenterPosition().y == aCenterPosition.y)
			myTurretsBottom[i]->SetDying();

	for (int i = 0; i < myTurretsMiddle.size(); i++)
		if (myTurretsMiddle[i]->GetCenterPosition().x == aCenterPosition.x && myTurretsMiddle[i]->GetCenterPosition().y == aCenterPosition.y)
			myTurretsMiddle[i]->SetDying();

	for (int i = 0; i < myTurretsTop.size(); i++)
		if (myTurretsTop[i]->GetCenterPosition().x == aCenterPosition.x && myTurretsTop[i]->GetCenterPosition().y == aCenterPosition.y)
			myTurretsTop[i]->SetDying();

}

bool T1_TurretManager::TurretAtPosition(glm::vec2 aCenterPosition) {
	if(aCenterPosition.y == 20.f)
		for (int i = 0; i < myTurretsBottom.size(); i++)
			if (myTurretsBottom[i]->GetCenterPosition().x == aCenterPosition.x && myTurretsBottom[i]->GetCenterPosition().y == aCenterPosition.y)
				return true;

	if(aCenterPosition.y == 40.f)
		for (int i = 0; i < myTurretsMiddle.size(); i++)
			if (myTurretsMiddle[i]->GetCenterPosition().x == aCenterPosition.x && myTurretsMiddle[i]->GetCenterPosition().y == aCenterPosition.y)
				return true;
	if(aCenterPosition.y == 60.f)
		for (int i = 0; i < myTurretsTop.size(); i++)
			if (myTurretsTop[i]->GetCenterPosition().x == aCenterPosition.x && myTurretsTop[i]->GetCenterPosition().y == aCenterPosition.y)
				return true;
	return false;
}
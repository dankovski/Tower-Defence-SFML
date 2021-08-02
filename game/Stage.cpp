#include "Stage.h"
#include <iostream>




Stage::Stage(std::vector<int> mMonsterQuantity, float mRespTime) {
	respTime = mRespTime;
	monsterQuantity = mMonsterQuantity;
	monstersToKill = 0;
	for (int i = 0; i < monsterQuantity.size(); i++) {
		
		monstersToKill += monsterQuantity[i];
	}
	monstersKilled = 0;
	monsterRespawned = 0;
}

void Stage::startStage()
{
	stageTime = 0;
}

int Stage::getMonsterId()
{
	int tmp = monsterRespawned;
	for (int i = 0; i < monsterQuantity.size(); i++) {
		if (tmp <= monsterQuantity[i]) {
			return i;
		}
		else {
			tmp -= monsterQuantity[i];
		}
	}

	return 0;
}



bool Stage::canMonsterSpawn(float mGameSpeed)
{

	if ((stageTime >= respTime/mGameSpeed) && monsterRespawned<monstersToKill) {
		monsterRespawned++;
		stageTime -= respTime / mGameSpeed;
		return true;
	}
	else {
		return false;
	}
}

bool Stage::isStageCompleted()
{
	if (monstersKilled == monstersToKill) {
		return true;
	}
	else {
		return false;

	}
		
}

void Stage::addMonsterKilled()
{
	monstersKilled++;
}

void Stage::render(double mDeltaTime)
{
	stageTime += mDeltaTime;
}








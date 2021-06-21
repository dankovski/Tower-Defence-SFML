#pragma once
#include <vector>

class Stage
{

	std::vector<int> monsterQuantity;
	std::vector<int> monsterAlreadyRespawned;
	double lastRespTime;
	float respTime;
	int monstersToKill;
	int monstersKilled;
	int monsterRespawned;

public:
	Stage(std::vector<int> mMonsterQuantity, float mRespTime);
	void startStage();
	int getMonsterId();
	bool canMonsterSpawn(float mGameSpeed);
	bool isStageCompleted();
	void addMonsterKilled();
};

